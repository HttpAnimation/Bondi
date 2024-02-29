import os
import re

def remove_comments(file_path):
    with open(file_path, 'r') as file:
        content = file.read()

    content = re.sub(r'#.*', '', content)

    content = re.sub(r'(\'\'\'(.|\n)*?\'\'\'|\"\"\"(.|\n)*?\"\"\")', '', content)

    with open(file_path, 'w') as file:
        file.write(content)

def process_python_scripts(directory='.'):
    python_files = [file for file in os.listdir(directory) if file.endswith('.py')]

    for file in python_files:
        file_path = os.path.join(directory, file)
        remove_comments(file_path)
        print(f"Comments removed from {file_path}")

if __name__ == "__main__":
    process_python_scripts()
