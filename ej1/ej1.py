#!/usr/bin/env python3
# -*- coding: utf-8 -*-

def generar_tabla_de_bordes(text):
	bordes = [-1]*(len(text)+1) # O(|text|)
	for i in range(1,len(bordes)): # O(|text|)
		j = bordes[i-1]
		while(j>=0 and text[i-1] != text[j]):
			j = bordes[j]
		bordes[i] = j+1
	return bordes

def es_substring(nombre, apodo):
	if(len(apodo) > len(nombre)):
		return False
	tabla_de_bordes = generar_tabla_de_bordes(apodo+nombre) # O(|nombre|+|apodo|) = O(n)
	largo_buscado = len(apodo) 		# O(|apodo|) = O(n)
	for i in tabla_de_bordes: 		# O(n)
		if i >= largo_buscado: 		# O(1)
			return True 			# O(1)
	return False 					# O(1)

palabra = input();
apodo = input();

print("S" if es_substring(palabra, apodo) else "N")
