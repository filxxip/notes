from flask import Flask, jsonify
from flask_sqlalchemy import SQLAlchemy

app = Flask(__name__)
app.config['SQLALCHEMY_DATABASE_URI'] = 'sqlite:///mydatabase.db'
db = SQLAlchemy(app)


@app.after_request
def commit_changes(response):
    print("hello")
    db.session.commit()
    return response


def save_session(function: callable):
    def wrapper(*args, **kwargs):
        with app.app_context():
            result = function(*args, **kwargs)
            session.commit()
            return result

    return wrapper


class MyModel(db.Model):
    __tablename__ = "MyModel"
    id = db.Column(db.Integer, primary_key=True)
    name = db.Column(db.String(50))
    value = db.Column(db.Float)


def create_mymodel(name, value, session):
    mymodel = MyModel(name=name, value=value)
    session.add(mymodel)
    # commit_changes(session)


def commit_changes(session):
    session.commit()


@app.route('/add')
# @save_session
def hello():
    mymodel = MyModel(name="filip", value=20)
    session.add(mymodel)
    # session.commit()
    return "added"


@app.route("/all")
def show():
    return jsonify([{pair: x.__dict__[
        pair] for pair in x.__dict__ if pair[0][0] != "_"} for x in MyModel.query.all()])


if __name__ == '__main__':
    with app.app_context():
        # create a new session
        # app.run()
        db.drop_all()
        db.create_all()
        session = db.session()
        app.run()

        # create and add MyModel object to the database
        create_mymodel('Test', 1.23, session)

        # commit changes to the database
        # commit_changes(session)

        # retrieve the MyModel object from the database
        mymodel2 = MyModel.query.filter_by(name='Test').all()
        print(mymodel2)
        # print('Retrieved MyModel with ID {}: name={}, value={}'.format(mymodel2.id, mymodel2.name, mymodel2.value))
