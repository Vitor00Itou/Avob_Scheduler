# Script para compilação e executação do programa

# Compilação do programa
echo "Compilando o programa..."

# Compilador + arquivos c++ + nome do arquvio + parametro para otimização da compilação
g++ src/*.cpp -o build/avob_scheduler -O3

# Verifica se houve erro na compilação
if [ $? -eq 0 ]; then
    echo "Compilação bem-sucedida."
else
    echo "Erro durante a compilação."
fi