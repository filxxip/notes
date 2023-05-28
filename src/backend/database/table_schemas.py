people_schema = {
    "type": "object",
    "properties": {
        "name": {"type": "string"},
        "surname": {"type": "string"},
        "email": {"type": "string"},
        "password": {"type": "string"},
        "country": {"type": "string"},
        "birthday": {"type": "string"},
        "created": {"type": "string"},
        "gender": {"enum": ["male", "female"]}
    },
    "additionalProperties": False
}

id_schema = {
    "type": "object",
    "properties": {
        "index": {"type": ["number", "string"]},
        "pid": {"type": ["number", "string"]}
    },
    "additionalProperties": False
}

notes_schema = {
    "type": "object",
    "properties": {
        "category": {"type": ["number", "string"]},
        "owner": {"type": ["number", "string"]},
        "title": {"type": "string"},
        "content": {"type": "string"},
        "releaseDate": {"type": "string"},
    },
    "additionalProperties": False
}

category_schema = {
    "type": "object",
    "properties": {
        "name": {"type": "string"},
        "owner": {"type": ["number", "string"]},
        "color": {"type": "string"},
        "creationDate": {"type": "string"},
    },
    "additionalProperties": False
}

guidialog_schema = {
    "type": "object",
    "properties": {
        "content": {"type": "string"},
        "title": {"type": "string"},
        "isOk": {"type": "string"},
        "isYes": {"type": "string"},
        "isNo": {"type": "string"},
        "path": {"type": "string"},
        "fontSize": {"type": ["number", "string"]}

    },
    "additionalProperties": False
}

schema_schema = {
    "type": "object",
    "properties": {
        "name": {"type": "string"},
        "schema": {"type": "string"}  # should be dict
    },
    "additionalProperties": False
}
