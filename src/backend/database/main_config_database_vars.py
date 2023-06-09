import datetime

from .constants import api_data
from flask import Flask
from flask.json import JSONEncoder
from sqlalchemy import create_engine
from sqlalchemy.orm import scoped_session, sessionmaker

app = Flask(__name__)
app.config['SQLALCHEMY_DATABASE_URI'] = api_data.database_name


class CustomJSONEncoder(JSONEncoder):
    def default(self, obj):
        if isinstance(obj, datetime.datetime):
            return obj.strftime(api_data.date_syntax)
        else:
            return super().default(obj)


app.json_encoder = CustomJSONEncoder
engine = create_engine(app.config['SQLALCHEMY_DATABASE_URI'], pool_size=50, max_overflow=100, pool_timeout=10)
db_session = scoped_session(sessionmaker(autocommit=False, autoflush=False, bind=engine))
