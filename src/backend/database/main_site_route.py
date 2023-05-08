from .utils import jsonify_result
from .main_config_database_vars import app

from .constants import api_data


@jsonify_result
@app.route(api_data.main_site)
def main_site():
    return api_data.main_site_information
