#
# Upload QA
# 

from gitlab import gitlab
from sys import argv
import json

# print(argv)
print("""
Upload file
Gitlab URL : %s
Repository Name : %s
Upload File : %s
Commit SHA : %s
"""%(argv[1], argv[2], argv[4], argv[5]))

g = gitlab(argv[1], argv[2], argv[3])
adr = g.uploadFile(argv[4],True)
commit_sha = argv[5]

adr = adr.decode('utf8').replace("'", '"')
adr = json.loads(adr)

content = """
Test QA
COMMIT SHA: %s

Produced MC File (ROOT): %s

"""%(commit_sha, adr["markdown"])

print(content)

g.postIssue("Test QA %s"%(commit_sha[0:8]), description=content, labels="Test QA, QA")




