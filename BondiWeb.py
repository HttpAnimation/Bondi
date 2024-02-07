import os
from flask import Flask, render_template
from selenium import webdriver

app = Flask(__name__)

@app.route('/')
def index():
    return render_template('index.html')

def open_browser_to_localhost():
    chrome_driver_path = "chromedriver" 
    url = "http://localhost"
    options = webdriver.ChromeOptions()
    options.add_argument("--kiosk")  
    driver = webdriver.Chrome(executable_path=chrome_driver_path, options=options)
    driver.get(url)

if __name__ == "__main__":
    open_browser_to_localhost()
    app.run(debug=False)
