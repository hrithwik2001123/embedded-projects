import cv2
import numpy as np
import RPi.GPIO as GPIO
import time
import math
import heapq
from flask import *
import threading
from ultralytics import YOLO
from picamera2 import Picamera2

picam = Picamera2()
picam.preview_configuration.main.size = (1080,720)
picam.preview_configuration.main.format = "RGB888"
picam.preview_configuration.main.align()
picam.configure("preview")
picam.start()

model = YOLO("/home/pi/AquaBoat/runs/detect/train/weights/best.pt")
threshold = 0.5

battery_value = 0

app = Flask(__name__)
command = None
objjjjjj = "No Detection"

BIN_STATUS="Normal"

frame = None
frame_lock = threading.Lock()

GPIO.setmode(GPIO.BCM)
GPIO.setwarnings(False)

IN1=13
IN2=27
IN3=22
IN4=23

BIN=26

CON_IN5=19

TRIG=5
ECHO=6

man_flag=0
aut_flag=0

GPIO.setup(IN1,GPIO.OUT)
GPIO.setup(IN2,GPIO.OUT)
GPIO.setup(IN3,GPIO.OUT)
GPIO.setup(IN4,GPIO.OUT)

GPIO.setup(CON_IN5,GPIO.OUT)

GPIO.setup(BIN,GPIO.IN)

GPIO.setup(TRIG,GPIO.OUT)
GPIO.setup(ECHO,GPIO.IN)


def conveyer_on():
    GPIO.output(CON_IN5,1)

def conveyer_off():
    GPIO.output(CON_IN5,0)

def forward():
    GPIO.output(IN1,1)
    GPIO.output(IN2,0)
    GPIO.output(IN3,1)
    GPIO.output(IN4,0)

def stop():
    GPIO.output(IN1,0)
    GPIO.output(IN2,0)
    GPIO.output(IN3,0)
    GPIO.output(IN4,0)

def backward():
    GPIO.output(IN1,0)
    GPIO.output(IN2,1)
    GPIO.output(IN3,0)
    GPIO.output(IN4,1)

def turn_left():
    GPIO.output(IN1,0)
    GPIO.output(IN2,0)
    GPIO.output(IN3,1)
    GPIO.output(IN4,0)
    time.sleep(0.7)
    stop()

def turn_right():
    GPIO.output(IN1,1)
    GPIO.output(IN2,0)
    GPIO.output(IN3,0)
    GPIO.output(IN4,0)
    time.sleep(0.7)
    stop()


def get_distance():

    GPIO.output(TRIG,False)
    time.sleep(0.05)

    GPIO.output(TRIG,True)
    time.sleep(0.00001)
    GPIO.output(TRIG,False)

    start=time.time()
    end=time.time()

    while GPIO.input(ECHO)==0:
        start=time.time()

    while GPIO.input(ECHO)==1:
        end=time.time()

    duration=end-start
    distance=duration*17150
    print(distance)

    return distance

GRID_SIZE=30

grid=np.zeros((GRID_SIZE,GRID_SIZE))

robot_x=0
robot_y=0

goal=None

direction="SOUTH"

zigzag_points = [
    (0,0), (0,29),
    (1,29), (1,0),
    (2,29)

]

point_index = 0
zigzag_mode = False

border_points = [
    (0,0),
    (0,29),
    (29,29),
    (29,0),
    (0,0)
]

border_mode = False
border_index = 0

def heuristic(a,b):
    return abs(a[0]-b[0])+abs(a[1]-b[1])

def astar(grid,start,goal):

    neighbors=[(1,0),(-1,0),(0,1),(0,-1)]

    close=set()
    came_from={}

    gscore={start:0}
    fscore={start:heuristic(start,goal)}

    open_list=[]
    heapq.heappush(open_list,(fscore[start],start))

    while open_list:

        current=heapq.heappop(open_list)[1]

        if current==goal:

            path=[]
            while current in came_from:
                path.append(current)
                current=came_from[current]

            return path[::-1]

        close.add(current)

        for i,j in neighbors:

            neighbor=(current[0]+i,current[1]+j)

            if not (0<=neighbor[0]<GRID_SIZE and 0<=neighbor[1]<GRID_SIZE):
                continue

            # DISABLED OBSTACLE AVOIDANCE
            # if grid[neighbor]==1:
            #     continue

            tentative_g=gscore[current]+1

            if neighbor in close and tentative_g>=gscore.get(neighbor,0):
                continue

            if tentative_g<gscore.get(neighbor,9999):

                came_from[neighbor]=current
                gscore[neighbor]=tentative_g
                fscore[neighbor]=tentative_g+heuristic(neighbor,goal)

                heapq.heappush(open_list,(fscore[neighbor],neighbor))

    return []


def update_obstacle():

    global grid

    if direction=="EAST" and robot_x+1<GRID_SIZE:
        grid[robot_x+1][robot_y]=1

    elif direction=="WEST" and robot_x-1>=0:
        grid[robot_x-1][robot_y]=1

    elif direction=="NORTH" and robot_y-1>=0:
        grid[robot_x][robot_y-1]=1

    elif direction=="SOUTH" and robot_y+1<GRID_SIZE:
        grid[robot_x][robot_y+1]=1

def rotate_to(target):

    global direction

    dirs=["NORTH","EAST","SOUTH","WEST"]

    current_index=dirs.index(direction)
    target_index=dirs.index(target)

    diff=(target_index-current_index)%4

    if diff==1:
        turn_right()
    elif diff==2:
        turn_right()
        turn_right()
    elif diff==3:
        turn_left()

    direction=target

def move_forward():
    forward()
    time.sleep(0.4)
    #stop()

def move_to(next_node):
    global robot_x, robot_y

    dx = next_node[0] - robot_x
    dy = next_node[1] - robot_y

    target = None

    if dx > 0:
        target = "EAST"
    elif dx < 0:
        target = "WEST"
    elif dy > 0:
        target = "SOUTH"
    elif dy < 0:
        target = "NORTH"

    if target is None:
        print("Already at node or invalid move:", next_node)
        return

    rotate_to(target)
    move_forward()

    if dx > 0:
        robot_x += 1
    elif dx < 0:
        robot_x -= 1
    elif dy > 0:
        robot_y += 1
    elif dy < 0:
        robot_y -= 1

@app.route('/api/command', methods=['POST'])
def receive_command():
    global goal, zigzag_mode, point_index, border_mode, border_index

    data = request.json
    cmd = data.get("command","").upper()

    if cmd=="A" and aut_flag==1:
        zigzag_mode=True
        point_index=0
        border_mode=False

    elif cmd=="B" and aut_flag==1:
        zigzag_mode=False
        border_mode=True
        border_index=0
        goal=None

    elif cmd=="C" and aut_flag==1:
        zigzag_mode=False
        border_mode=False
        goal=(15,15)

    elif cmd=="D" and aut_flag==1:
        zigzag_mode=False
        border_mode=False
        goal=(10,20)

    elif cmd=="E" and aut_flag==1:
        zigzag_mode=False
        border_mode=False
        goal=(0,0)

    return jsonify({"status":"success","command":cmd})

@app.route('/control', methods=['POST'])
def control():
    global man_flag
    try:
        data = request.get_json()
        rec_data = data.get('command', '')
        print(rec_data)
        
        if rec_data == 'A' and man_flag==1:
            forward()
        elif rec_data == 'B' and man_flag==1:
            backward()
        elif rec_data == 'C' and man_flag==1:
            turn_left()
        elif rec_data == 'D' and man_flag==1:
            turn_right()
        elif rec_data == 'E' and man_flag==1:
            stop()

        return jsonify({'status': 'success', 'command': rec_data}), 200
    except Exception as e:
        print(e)
        return jsonify({'status': 'error', 'message': str(e)}), 500

@app.route('/conveyer', methods=['POST'])
def conveyer():
    try:
        data_con = request.get_json()
        con = data_con.get('command', '')
        print(con)
        if con == "A":
            conveyer_on()
        elif con == "B":
            conveyer_off()
        return jsonify({'status': 'success', 'command': con}), 200
    except Exception as e:
        print(e)
        return jsonify({'status': 'error', 'message': str(e)}), 500

@app.route('/automatic', methods=['POST'])
def automatic():
    global man_flag,aut_flag
    try:
        data_aut_check = request.get_json()
        data_aut = data_aut_check.get('command', '')
        print(data_aut)
        if data_aut == 'A':
            man_flag=1
            aut_flag=0
        elif data_aut == 'B':
            man_flag=0
            aut_flag=1
        return jsonify({'status': 'success', 'command': data_aut}), 200
    except Exception as e:
        print(e)
        return jsonify({'status': 'error', 'message': str(e)}), 500

@app.route('/yolo', methods=['POST','GET'])
def yolo_detect():
    global objjjjjj
    try: 
        return jsonify({'status': 'success', 'object': objjjjjj}), 200
    except Exception as e:
        print(e)
        return jsonify({'status': 'error', 'message': str(e)}), 500

def robot_loop():
    global point_index, zigzag_points, robot_x, robot_y, zigzag_mode, goal,border_mode,border_index,border_points

    while True:
        distance = get_distance()
        print("Distance = ",distance)

        if distance < 10:
            stop()
            print("Obstacle Detected!")
            update_obstacle()
            obj = detect()
            print(obj)
            if obj:
                conveyer_on()
                time.sleep(3)
                conveyer_off()
                time.sleep(3)
                continue
            continue
        
        if border_mode:
            if border_index>=len(border_points):
                print("Border Path Completed")
                stop()
                border_mode=False
                continue

            target=border_points[border_index]

            if (robot_x,robot_y)==target:
                print("Reached:", target)
                border_index+=1
                continue

            move_to(target)
            time.sleep(0.1)
            continue

        if zigzag_mode:

            if point_index >= len(zigzag_points):
                print("Zig-Zag Path Completed")
                stop()
                zigzag_mode = False
                goal = None
                time.sleep(0.5)
                continue

            target = zigzag_points[point_index]

            if (robot_x, robot_y) == target:
                print("Reached:", target)
                point_index += 1
                continue

            move_to(target)
            time.sleep(0.1)
            continue

        if goal is None:
            time.sleep(0.5)
            continue

        path = astar(grid, (robot_x, robot_y), goal)

        if len(path) > 0:
            next_node = path[0]
            move_to(next_node)

        if (robot_x, robot_y) == goal:
            print("Goal reached")
            goal = None
            stop()

        if cv2.waitKey(1) == 27:
            break

def detect():
    global frame, objjjjjj

    try:
        with frame_lock:
            if frame is None:
                return None
            temp_frame = frame.copy()

        temp_frame = cv2.resize(temp_frame, (320,320))

        results = model(temp_frame)[0]

        best_obj = None
        best_score = 0

        for result in results.boxes.data.tolist():
            x1,y1,x2,y2,score,class_id = result

            if score > threshold and score > best_score:
                best_score = score
                best_obj = results.names[int(class_id)]

        if best_obj:
            objjjjjj = best_obj
            print("Detected:", best_obj)
            return best_obj
        else:
            objjjjjj = "No Detection"
            return None

    except Exception as e:
        print("Detection Error:", e)
        return None

def generate_frames():
    global frame

    while True:
        try:
            with frame_lock:
                frame = picam.capture_array()
                
                temp = frame.copy()

            ret, buffer = cv2.imencode('.jpg', temp)
            if not ret:
                continue

            yield (b'--frame\r\n'
                   b'Content-Type: image/jpeg\r\n\r\n' + buffer.tobytes() + b'\r\n')

            time.sleep(0.03)

        except Exception as e:
            print("Camera Error:", e)

@app.route('/')
def video_feed():
    return Response(generate_frames(),
                    mimetype='multipart/x-mixed-replace; boundary=frame')

def buffering():
    global BIN_STATUS
    while True:
        try:
            global BIN_STATUS
            BIN_VAL = GPIO.input(BIN)
            if BIN_VAL==0:
                BIN_STATUS="Full"
            else:
                BIN_STATUS="Normal"
        except Exception as e:
            print("Error:", e)
            time.sleep(2)

@app.route('/get_data', methods=['POST','GET'])
def get_data():
    global BIN_STATUS,battery_value
    try:
        return jsonify({'status': 'success','battery':battery_value,'bin_status':BIN_STATUS }), 200
    except Exception as e:
        print(e)
        return jsonify({'status': 'error', 'message': str(e)}), 500

@app.route('/battery', methods=['POST'])
def battery():
    global battery_value
    try:
        data = request.get_json()
        battery_value = data.get("battery",0)
        print("Battery % =",battery_value)
        return jsonify({'status': 'success','battery':battery_value }), 200
    except Exception as e:
        print(e)
        return jsonify({'status': 'error', 'message': str(e)}), 500

threading.Thread(target=robot_loop).start()
threading.Thread(target=buffering).start()

app.run(host='0.0.0.0',port=5000)
