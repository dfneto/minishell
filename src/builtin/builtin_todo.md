# Builtins

## Echo
### O que deve fazer?
Mostrar texto no terminal  
### O que faz no momento?
Mostra texto no terminal
### TO DO:
Acredito que nada

## Cd
### O que deve fazer?
Trocar folder (segundo o subject: with only a relative or absolute path)  
### O que faz no momento?
Troca de folder...  
### TO DO:
- Alterar no env o PWD e o OLDPWD: a função cd original altera essas variaveis quando troca de pasta.
    - folder original minishell
    - cd src -> muda para folder src
    - PWD é altearada para minishell/src
    - OLDPWD é alterada para minishell
- Estou usando getenv que pega do env original e acho que nao deveria ser usado. Criar função "ft_getenv" que pega do nosso env.  
- **ft_getenv depende de definir se vamos trocar o env pra lista ou seguimos com array.**  
## Pwd
### O que deve fazer?
Imprimir folder atual  
### O que faz no momento?
Imprime folder atual  
### TO DO:
Acredito que nada. Pelo que entendi a função getcwd não depende das env para pegar o cwd correto  

## Export
### O que deve fazer?
Export sozinho deve imprimir todas as variáveis de ambiente (inclusive as que não tem valor) em ordem alfabética. Export com argumentos deve adicionar/modificar as variaveis correspondentes  
### O que faz no momento?
Imprime env em ordem e adiciona (não substitui e não faz comprovação se já existe para modificar...)  
### TO DO:
- **Essa função ainda depende de definir se vamos trocar o env pra lista ou seguimos com array.**  
- Implementar a busca se a variavel existe e substituir;  
- Se mantiver como array, verificar se a impressão ou modificação não destroi o env.  

## Unset
### O que deve fazer?
Remove variaveis de ambiente!  
### O que faz no momento?
Imprime uma frase linda dizendo que não existe essa função  
### TO DO:
Tudo...  
Unset pode usar a função de buscar variavel criada para a função export  
**Essa função ainda depende de definir se vamos trocar o env pra lista ou seguimos com array.**  

## Env
### O que deve fazer?
Imprime env na ordem que ele estiver (que para mim parece random...)  
Só imprime variaveis que tenham valor.  
### O que faz no momento?
Imprime todas as variaveis  
### TO DO:
**Essa função ainda depende de definir se vamos trocar o env pra lista ou seguimos com array.**  

## Exit
### O que deve fazer?
Sair do programa com código que for passado como variável  
### O que faz no momento?
Sair do programa com código que for passado como variável  
### TO DO:
Acredito que nada  

