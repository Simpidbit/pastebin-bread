import requests

def sendPostMsg(url, data):
    try:
        response = requests.post(url, data = data)
        return response.text
    except:
        return "Error!"
