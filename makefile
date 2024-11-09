etapa:=1

compilar:
	gcc T2_etapa$(etapa)_pedrosilva_guilhermejose_eduardofernandes_106.c -o bin/etapa$(etapa).exe

rodar:
	./bin/etapa$(etapa).exe