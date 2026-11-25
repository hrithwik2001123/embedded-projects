from flask import Flask, request, jsonify
import pymysql
import os
from werkzeug.utils import secure_filename
from datetime import datetime
import logging

app = Flask(__name__)


try:
    con = pymysql.connect(host='localhost', port=3306, user='root', password='root', db='wildanimal_intrusion', charset='utf8')
    cmd = con.cursor()
    print("DB connected")
except pymysql.Error as e:
    print("Error connecting to MySQL:", e)

sensor_data = {
    "temperature": 25.5,
    "humidity": 60,
    "moisture": "LOW"
}

# Pump status
pump_status = {"state": "OFF"}

logging.basicConfig(level=logging.INFO)


@app.route('/register', methods=['POST', 'GET'])
def register():
    try:
        first_name = request.form.get('First_Name')
        last_name = request.form.get('Last_Name')
        address = request.form.get('Address')
        email = request.form.get('Email')
        password = request.form.get('Password')
        location = request.form.get('Location')
        phone_number = request.form.get('Phone_Number')

        print(first_name, last_name, address, email, password, location, phone_number)

        if not all([first_name, last_name, address, email, password, location, phone_number]):
            return jsonify({'message': 'All fields are required!'}), 400

        cmd.execute("SELECT * FROM registration WHERE email = %s OR phonenumber = %s", (email, phone_number))
        existing_user = cmd.fetchone()
        if existing_user:
            return jsonify({'message': 'User already exists!'}), 400

        cmd.execute("INSERT INTO login (email, password, usertype) VALUES (%s, %s, %s)", (email, password, 'user'))
        con.commit()

        login_id = cmd.lastrowid

        cmd.execute(
            """INSERT INTO registration 
            (first_name, last_name, address, email, location, phonenumber, login_id) 
            VALUES (%s, %s, %s, %s, %s, %s, %s, %s)""",
            (first_name, last_name, address, email, location, phone_number, login_id)
        )
        con.commit()

        return jsonify({'message': 'success'}), 200

    except Exception as e:
        print(e)
        return jsonify({'message': 'Error processing request'}), 500


    except Exception as e:
        print(e)
        return jsonify({'message': f'Registration failed: {str(e)}'}), 500


@app.route('/login', methods=['POST', 'GET'])
def login():
    try:
        data = request.get_json()
        email = data.get('username')
        password = data.get('password')
        print(email, password)

        if not email or not password:
            return jsonify({'message': 'All fields are required'}), 400

        cmd.execute("SELECT id, email, password FROM login WHERE email = %s AND usertype = %s", (email, 'user'))
        user = cmd.fetchone()
        if user:
            user_id = user[0]
            cmd.execute("SELECT * FROM registration WHERE email = %s AND login_id = %s", (email, user_id))
            reg_user = cmd.fetchone()
            print(reg_user)
            if reg_user:
                firstname = reg_user[1]
                lastname = reg_user[2]
                address = reg_user[3]
                location = reg_user[5]
                phone_number = reg_user[6]


        return jsonify({
            'message': 'success',
            'id': user_id,
            'firstname':firstname,
            'lastname':lastname,
            'address':address,
            'location':location,
            'phone':phone_number
        }), 200

    except Exception as e:
        print(e)
        return jsonify({'message': f'Error: {str(e)}'}), 500

@app.route('/updateProfile/<int:user_id>', methods=['PUT'])
def update_profile(user_id):
    try:
        data = request.get_json()
        
        # Extract profile data
        first_name = data.get('firstname')
        last_name = data.get('lastname')
        address = data.get('address')
        location = data.get('location')
        phone_number = data.get('phone')

        # Validate required fields
        if not all([first_name, last_name, phone_number]):
            return jsonify({'message': 'First name, last name, and phone number are required!'}), 400

        # Update user profile in the database
        cmd.execute("""
            UPDATE registration 
            SET first_name = %s, 
                last_name = %s, 
                address = %s, 
                location = %s, 
                phonenumber = %s 
            WHERE login_id = %s
        """, (first_name, last_name, address, location, phone_number, user_id))
        
        # Commit the changes
        con.commit()

        return jsonify({
            'message': 'Profile updated successfully',
            'firstname': first_name,
            'lastname': last_name,
            'address': address,
            'location': location,
            'phone': phone_number
        }), 200

    except Exception as e:
        print(e)
        con.rollback()
        return jsonify({'message': f'Error updating profile: {str(e)}'}), 500

@app.route('/get_notifications/<user_id>', methods=['GET'])
def get_notifications(user_id):
    try:
        query = '''
            SELECT animal_name, timestamp
            FROM notifications
            WHERE user_id = %s
            ORDER BY timestamp DESC
        '''

        cmd.execute(query, (user_id,))
        notifications = cmd.fetchall()

        if notifications:
            return jsonify({'status': 'success', 'notifications': notifications}), 200
        else:
            return jsonify({'status': 'success', 'notifications': []}), 200

    except Exception as e:
        print(f"Error: {e}")
        return jsonify({'status': 'error', 'message': str(e)}), 500
    
@app.route('/get_animals/<user_id>', methods=['GET'])
def get_animals(user_id):
    try:
        query = "SELECT animal_name, animal_image, timestamp FROM animals WHERE user_id = %s"
        cmd.execute(query, (user_id,))
        animals_data = cmd.fetchall()

        if animals_data:
            response = {
                "status": "success",
                "animals": animals_data,
            }
        else:
            response = {
                "status": "no_data",
                "message": "No animal intrusion data found for this user.",
            }

        return jsonify(response)
    except Exception as e:
        return jsonify({"status": "error", "message": str(e)})

    

@app.route('/readings', methods=['GET'])
def get_readings():
    return jsonify(sensor_data)

@app.route('/pump/on', methods=['POST'])
def turn_pump_on():
    pump_status["state"] = "ON"
    return jsonify({"message": "Pump turned ON", "status": pump_status["state"]})

@app.route('/pump/off', methods=['POST'])
def turn_pump_off():
    pump_status["state"] = "OFF"
    return jsonify({"message": "Pump turned OFF", "status": pump_status["state"]})
    
    


if __name__ == '__main__':
    app.run(port=5000, host='0.0.0.0')
