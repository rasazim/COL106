from hugchat import hugchat
from hugchat.login import Login
import sys


if __name__ == '__main__':
    if len(sys.argv)<5:
        print("Usage: python api_call.py user_email passwd num_paragraphs query.txt")
        sys.exit(1)
    
    email = sys.argv[1]
    password = sys.argv[2]
    num_paragraphs = sys.argv[3]
    print(num_paragraphs)

    paragraphs = []

    for i in range(num_paragraphs):
        filename = 'paragraph_' + str(i) + '.txt'
        print(filename)
        with open(filename, 'r') as f:
            paragraphs.append(f.read())
            paragraphs.append('\n')
    
    query_file = sys.argv[4]
    with open(query_file, 'r') as f:
        query = f.read()
        paragraphs.append(query)
        paragraphs.append('\n')
    
    paragraphs = '\n'.join(paragraphs)

    print(paragraphs)

    sign = Login(email, password)
    cookies = sign.login()

    chatbot = hugchat.ChatBot(cookies=cookies.get_dict())

    response = chatbot.query(paragraphs,web_search=False)

    print(response["text"])


    