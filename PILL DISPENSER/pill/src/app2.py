from flask import *
import pymysql
app= Flask(__name__)

# con = pymysql.connect(
#     host="localhost",   # 🔥 change from localhost
#     user="root",
#     password="root",
#     db="medicine_trolleydb",
#     port=3307,
#     charset="utf8"
# )
# cmd = con.cursor()
try:
    con = pymysql.connect(
        host="localhost",
        user="root",
        password="root",
        db="medicine_trolleydb",
        port=3307,
        charset="utf8"
    )
    cmd = con.cursor()
    print("Database connected successfully")
except Exception as e:
    print("Database connection failed:", e)
    con = None
    cmd = None


@app.route("/caretaker/register", methods=['POST','GET'])
def caretaker_register():
    print(request.form)

    # Get form data
    Full_name = request.form.get("Full_name")
    Phone = request.form.get("Phone")
    email = request.form.get("email")
    gender = request.form.get("gender")
    dob = request.form.get("dob")
    password = request.form.get("password")
    address = request.form.get("address")
    exp = request.form.get("exp")
    Proof = request.form.get("Proof")

    # Get uploaded file
    proof_image = request.files.get("proof_image")
    print(proof_image)

    print(Full_name, Phone, email, gender, dob, password, address, exp, Proof, proof_image)

    # Save image
    if proof_image:
        image_path = "static/uploads/" + proof_image.filename
        proof_image.save(image_path)
    else:
        return jsonify({"status": "Image missing"}), 400

    # Check duplicate user
    cmd.execute(
        "SELECT * FROM userdetails WHERE email=%s OR Phone=%s",
        (email, Phone)
    )
    res = cmd.fetchone()

    if res is None:
        # Insert into login table
        cmd.execute(
            "INSERT INTO login (username, pasword, type) VALUES (%s, %s, 'user')",
            (email, password)
        )
        con.commit()

        loginid = cmd.lastrowid

        # Insert into userdetails table
        cmd.execute("""
            INSERT INTO userdetails 
            (Full_name, Phone, email, gender, dob, address, exp, Proof, Proof_image, LOGINID)
            VALUES (%s,%s,%s,%s,%s,%s,%s,%s,%s,%s)
        """, (
            Full_name,
            Phone,
            email,
            gender,
            dob,
            address,
            exp,
            Proof,
            image_path,
            loginid
        ))
        con.commit()

        return jsonify({"status": "success"}), 201

    else:
        return jsonify({"status": "Already Registered"}), 409


@app.route("/logincheck", methods=['POST'])
def logincheck():
    try:
        # Get JSON data properly
        data = request.get_json()

        if not data:
            return jsonify({
                "task": "invalid data",
                "message": "No JSON received"
            }), 400

        # Get email and password
        email = data.get("email")
        password = data.get("password")

        print("Email:", email)
        print("Password:", password)

        # Validate fields
        if not email or not password:
            return jsonify({
                "task": "missing fields"
            }), 400

        # Execute query safely
        cmd.execute(
            "SELECT * FROM login WHERE username=%s AND pasword=%s",
            (email, password)
        )
        result = cmd.fetchone()
        print("DB Result:", result)

        # If no user found
        if result is None:
            return jsonify({
                "task": "invalid"
            }), 401   # 🔥 IMPORTANT: return 401 for invalid login

        # If login success
        return jsonify({
            "task": "success",
            "loginid": result[0],
            "type": result[3]
        }), 200

    except Exception as e:
        print("Error:", str(e))
        return jsonify({
            "task": "error",
            "message": str(e)
        }), 500


@app.route("/patients/register", methods=['POST'])
def register_patient():
    try:
        # Get JSON data
        data = request.get_json()
        if not data:
            return jsonify({"status": "No data received"}), 400

        name = data.get("name")
        age = data.get("age")
        phone = data.get("phone")
        gender = data.get("gender")
        disease = data.get("disease")
        description = data.get("description")
        USERID=data.get("lid")
        medicines = data.get("medicines", [])

        # Insert into patients table
        insert_patient = """
            INSERT INTO patient_table (name, age, phone, gender, disease, description,USERID)
            VALUES (%s, %s, %s, %s, %s, %s,%s)
        """
        cmd.execute(insert_patient, (name, age, phone, gender, disease, description,USERID))
        con.commit()
        patient_id = cmd.lastrowid  # get inserted patient ID

        # Insert medicines
        insert_medicine = """
            INSERT INTO medicines (patient_id, name, quantity, timing)
            VALUES (%s, %s, %s, %s)
        """
        for med in medicines:
            med_name = med.get("name")
            quantity = med.get("quantity")
            med_timing = med.get("timing")
            cmd.execute(insert_medicine, (patient_id, med_name, quantity, med_timing))

        con.commit()

        return jsonify({"status": "success", "patient_id": patient_id}), 201

    except Exception as e:
        print("Error:", e)
        return jsonify({"status": "error", "message": str(e)}), 500


from flask import request


@app.route("/allpatientdata/<int:loginid>", methods=['GET', 'POST'])
def allpatientdata(loginid):
    # Use the loginid from the URL
    userid = loginid
    print(f"Fetching data for USERID: {userid}")

    # Execute the JOIN query filtered by USERID
    cmd.execute("""
        SELECT patient_table.*, 
               medicines.id AS med_id, 
               medicines.name AS med_name, 
               medicines.quantity, 
               medicines.timing
        FROM patient_table
        LEFT JOIN medicines
        ON patient_table.id = medicines.patient_id
        WHERE patient_table.USERID = %s
    """, (userid,))

    rows = cmd.fetchall()
    header = [x[0] for x in cmd.description]

    patients = {}

    for row in rows:
        row_dict = dict(zip(header, row))
        patient_id = row_dict['id']

        # Initialize patient if not exists
        if patient_id not in patients:
            patients[patient_id] = {
                'id': patient_id,
                'name': row_dict['name'],
                'age': row_dict['age'],
                'phone': row_dict['phone'],
                'gender': row_dict['gender'],
                'disease': row_dict['disease'],
                'description': row_dict['description'],
                'USERID': row_dict.get('USERID'),
                'medicines': []
            }

        # Add medicine if exists
        if row_dict.get('med_id') is not None:
            patients[patient_id]['medicines'].append({
                'id': row_dict['med_id'],
                'name': row_dict['med_name'],
                'quantity': row_dict['quantity'],
                'timing': row_dict['timing']
            })

    # Convert dict to list for JSON
    json_data = list(patients.values())
    return jsonify(json_data)


@app.route('/update_medicine', methods=['GET','POST'])
def update_medicine():
    data = request.get_json()
    print(data)

    medicine_id = data.get('id')
    name = data.get('name')
    quantity = data.get('quantity')
    timing = data.get('timing')

    if not medicine_id:
        return jsonify({"error": "Medicine ID is required"}), 400

    cmd.execute("update medicines deatils set name='"+str(name)+"',quantity='"+str(quantity)+"',timing='"+str(timing)+"' where id='"+str(medicine_id)+"'")
    con.commit()
    return jsonify({"message": "Medicine updated successfully"}), 200

@app.route('/delete_medicine/<int:medicine_id>', methods=['GET','POST'])
def delete_medicine(medicine_id):
    try:
        print("Medicine ID from URL:", medicine_id)

        cmd.execute("DELETE FROM medicines WHERE id=%s", (medicine_id,))
        con.commit()

        if cmd.rowcount == 0:
            return jsonify({"message": "Medicine not found"}), 404

        return jsonify({"message": "Medicine deleted successfully"}), 200

    except Exception as e:
        return jsonify({"error": str(e)}), 500

@app.route('/add_medicine', methods=['POST','GET'])
def add_medicine():
    try:
        data = request.get_json()
        print(data)
        patient_id = data.get('patientId')
        name = data.get('name')
        quantity = data.get('quantity')
        timing = data.get('timing')

        # Validate fields
        if not patient_id or not name or not quantity or not timing:
            return jsonify({
                "message": "Missing required fields"
            }), 400

        cmd.execute("""
            INSERT INTO medicines (patient_id, name, quantity, timing)
            VALUES (%s, %s, %s, %s)
        """, (patient_id, name, quantity, timing))

        con.commit()

        return jsonify({
            "message": "Medicine added successfully"
        }), 201   # ✅ 201 = Created

    except Exception as e:
        return jsonify({
            "error": str(e)
        }), 500


@app.route('/latest_notification/<int:user_id>', methods=['GET'])
def latest_notification(user_id):
    try:
        sql = """
            SELECT n.id AS notification_id, n.message, n.date, n.patient_id, 
                   p.name AS patient_name, p.age, p.phone, p.gender, p.disease
            FROM notification n
            JOIN patient_table p ON n.patient_id = p.id
            WHERE p.USERID = %s
            ORDER BY n.date DESC
            LIMIT 1
        """
        cmd.execute(sql, (user_id,))
        result = cmd.fetchone()
        print(result)

        if result is None:
            return jsonify({"message": "No notifications found"}), 404

        return jsonify(result), 200

    except Exception as e:
        return jsonify({"error": str(e)}), 500

@app.route("/test")
def test():
    return "Flask is working!"

if __name__ == "__main__":
    print("-------------------------->")
    print(app.url_map)
    app.run(host='0.0.0.0',port=5000)