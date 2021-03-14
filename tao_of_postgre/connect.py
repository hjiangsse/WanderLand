import psycopg2

conn = None
conn = psycopg2.connect(
    host="localhost",
    database="hjianglab",
    user="hjiang",
    password="jiang186212")

cursor = conn.cursor()
cursor.execute("select * from weather")
