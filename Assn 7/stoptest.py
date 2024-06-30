
words=[]
with open("stops.txt","r") as f:
    words=f.readlines()

nwords=[]
for w in words:
    nwords.append(w[:-1])



sent = "vector<string> stops = {\""
sent+="\",\"".join(nwords)
sent+="\"};"

with open("stopsent.txt","w") as f:
    f.write(sent)


