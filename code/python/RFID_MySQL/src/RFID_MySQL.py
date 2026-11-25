import pymysql
from flask import Flask, request

# ===== Database connection =====
con = pymysql.connect(
    host='localhost',
    user='root',
    passwd='root',
    db='smart_cart',
    port=3306,
    charset='utf8'
)
cmd = con.cursor()

# ===== Flask app =====
app = Flask(__name__)


@app.route('/test', methods=['POST'])
def test():
    # Get raw data
    val = request.get_data().decode()  # example: "India Gate Rice,5kg,rs:400"
    res = val.split(',')

    # Split into fields
    items = res[0]
    kg = res[1]
    price = res[2]

    print("Received:", items, kg, price)

    # Insert into database
    cmd.execute("INSERT INTO cart_items VALUES (NULL, %s, %s, %s)", (items, kg, price))
    con.commit()
    print("✅ Data inserted into cart_items")

    return "ok"


# Run server
app.run(port=5000, debug=True, host='0.0.0.0')
