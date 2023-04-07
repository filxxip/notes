import socket
import json
from datetime import datetime
from sqlalchemy import create_engine, Column, Integer, String, DateTime, select
from sqlalchemy.orm import sessionmaker
from sqlalchemy.ext.declarative import declarative_base
from sqlalchemy.orm import DeclarativeBase, Mapped, mapped_column, sessionmaker
from sqlalchemy.types import DateTime, Integer, String
from sqlalchemy import ForeignKey, create_engine, Column
from functools import wraps
from pathlib import Path
from typing import Callable, Type, Protocol
from dataclasses import dataclass
from flask import *

from flask import Flask
from flask_sqlalchemy import SQLAlchemy
from sqlalchemy import Column
app = Flask(__name__)
app.config['SQLALCHEMY_DATABASE_URI'] = 'sqlite:///example.db'
db = SQLAlchemy(app)
print(db.Column)


class User(db.Model):
    id = db.Column(db.Integer, primary_key=True)
    username = db.Column(db.String(80), unique=True, nullable=False)
    email = db.Column(db.String(120), unique=True, nullable=False)

    def __repr__(self):
        return '<User %r>' % self.username


if __name__ == '__main__':
    app.run()

# people = [
#     {
#         "id": 0, "name": "Filip", "age": 19
#     },
#     {
#         "id": 1, "name": "Julka", "age": 18
#     },
#     {
#         "id": 2, "name": "Marcin", "age": 19
#     }
# ]


# @app.route("/")
# def index():
#     return f"Hej its admin"


# @app.route("/people", methods=["GET", "POST"])
# def index_with_name():
#     if request.method == "GET":
#         if len(people) > 0:
#             return jsonify(people)
#         else:
#             return 'Nothing Found', 404
#     if request.method == "POST":
#         name = request.form['name']
#         age = request.form['age']
#         id = people[-1]['id']+1
#         obj = {
#             "id": id, "name": name, "age": age
#         }
#         people.append(obj)
#         return jsonify(people),201


# @app.route('/person/<int:id>', methods = ["GET", "PUT", "DELETE"])
# def single_book(id):
#     global people
#     if request.method=='GET':
#         for person in people:
#             if person['id']==id:
#                 return jsonify(person)
#     if request.method == "PUT":
#         for person in people:
#             if person['id']==id:
#                 name = request.form['name']
#                 age = request.form['age']
#                 obj = {
#                     "id": id, "name": name, "age": age
#                 }
#                 return jsonify(obj)
#     if request.method == "DELETE":
#         people = [x for x in people if x["id"] != id]
#         return jsonify(people)


# if __name__ == "__main__":
#     app.run(debug=True)

# # # Define the database connection string
# path = "notebook_database.db"
# DATABASE_URL = rf"sqlite:///{path}"

# # Create the database engine and session
# engine = create_engine(DATABASE_URL)
# Session = sessionmaker(bind=engine)
# session = Session()

# # Define the database model using SQLAlchemy ORM
# Base = declarative_base()

# class Person(Base):
#     __tablename__ = "People"
#     id: Mapped[int] = mapped_column(
#         Integer(), primary_key=True, nullable=False, autoincrement=True)
#     name: Mapped[str] = mapped_column(String(50))
#     surname: Mapped[str] = mapped_column(String(50))
#     age: Mapped[int] = mapped_column(Integer())
#     email: Mapped[str] = mapped_column(String(50))
#     password: Mapped[str] = mapped_column(String(50))
#     country: Mapped[str] = mapped_column(String(50))
#     birthday: Mapped[str] = mapped_column(DateTime())

# # Create the socket and listen for connections
# sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
# sock.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
# sock.bind(('localhost', 9100))
# sock.listen(1)

# while True:
#     # Accept a connection and receive a signal from the C++ program
#     conn, addr = sock.accept()
#     signal = conn.recv(1024)

#     # Parse the signal as a JSON object
#     signal_data = json.loads(signal)

#     # Retrieve the record from the database based on the signal data
#     record = session.execute(select(Person).filter(
#         Person.name == signal_data['name'])).fetchall()
#     print(record)
#     print(record.__dict__)
#     # record = session.query(Person).filter(
#     #     Person.name == signal_data['name']).first()

#     # Send the record back to the C++ program as a JSON object
#     conn.sendall(json.dumps({
#         'name': record.name,
#         'surname': record.surname,
#         'age': str(record.age),
#     }).encode())

#     # Close the connection
#     conn.close()
