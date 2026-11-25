from flask import Flask, request

app = Flask(__name__)

@app.route('/test', methods=['POST'])
def test():
    val = request.get_data().decode()
    res=val.split(',')
    humidity=res[0]
    temperature=res[1]
    print(humidity,temperature)
    return "ok"

app.run(port=5000, debug=True, host='0.0.0.0')
