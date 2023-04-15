people_schema = {
    "type": "object",
    "properties": {
        "name": {"type": "string"},
        "surname": {"type": "string"},
        "email": {"type": "string"},
        "password": {"type": "string"},
        "country": {"type": "string"},
        "birthday": {"type": "string"}
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
        "color": {"type": "string"},
        "creationDate": {"type": "string"},
    },
    "additionalProperties": False
}