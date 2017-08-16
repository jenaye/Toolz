#coding: utf-8
n = int(raw_input("n : "))
e = int(raw_input("e : "))
c = int (raw_input("c : "))

cbis = c*pow(2,e,n)%n

print "A envoyer a l'oracle : {}".format(cbis)

res = int(raw_input("Réponse :"))
m = res / 2
print "Le résultat : {} \n Ou : {}".format(m, hex(m)[2:].replace('L', '').decode("hex"))
