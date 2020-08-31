import json

with open('database.txt') as f:
    emails = [line.strip().split('\t')[1] for line in f]

print(json.dumps(emails))
