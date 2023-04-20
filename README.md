# Primeiro Trabalho de TBO
Programa que resolve o problema de agrupamentos de diversos pontos em um espaço $R^m$, em que *m* é o número de dimensões do espaço.

# Arquivos de entrada
Os arquivos de entrada devem ser em formato *.txt*. Cada linha do arquivo representará um ponto do $R^m$ e deve ser composta por *m* + 1 campos separados por vírgulas. O primeiro elemento será um identificador único do ponto (cadeia de caracteres) e os demais *m* valores reais devem indicar a coordenada do ponto no $R^m$. Segue exemplo abaixo:
```
A,3.0,7.0
B,1.0,2.0
C,7.0,3.0
D,4.0,7.0
E,1.0,1.0
```

# Utilização
Para utilizar e compilar o código, deve ser utilizado o makefile, incluso nos
arquivos. O comando ```make``` irá gerar o executável do programa, chamado ```trab1```. 

# Execução
Para executar o programa, execute o seguinte comando:

```
./trab1 <arquivo_de_entrada.txt> k <arquivo_de_saida.txt>
```
O valor de k é o número de grupos a serem criados.


