#!/usr/bin/env python3
# -*- coding: utf-8 -*-

def generar_tabla_de_bordes(text):
	#print("Voy a buscar los bordes de %s"%text)
	bordes = [-1]*(len(text)+1) # O(|text|)
	for i in range(1,len(bordes)): # O(|text|)
		j = bordes[i-1]
		#print("i=%s, j=%s"%(i,j))
		while(j>=0 and text[i-1] != text[j]):
			#print("\t\twhile j=%s, text[i-1]=%s, text[j]=%s"%(j,text[i-1], text[j]))
			#print("\t\t j = %s, bordes[j]=%s"%(j,bordes[j]))
			j = bordes[j]
			#print("\t\t j = %s"%j)
		bordes[i] = j+1
		#print("\tbordes[%s]=%s"%(i,bordes[i]))
		#print("bordes=%s"%bordes)
	return bordes

def es_substring(nombre, apodo):
	if(len(apodo) > len(nombre)):
		return False
	tabla_de_bordes = generar_tabla_de_bordes(apodo+nombre) # O(|nombre|+|apodo|) = O(n)
	#print(tabla_de_bordes)
	largo_buscado = len(apodo) 		# O(|apodo|) = O(n)
	for i in tabla_de_bordes: 		# O(n)
		if i >= largo_buscado: 		# O(1)
			return True 			# O(1)
	return False 					# O(1)

palabra = input(); #print(palabra)
apodo = input(); #print(apodo)

print("S" if es_substring(palabra, apodo) else "N")