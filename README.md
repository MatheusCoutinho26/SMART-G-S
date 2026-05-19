# 💨 SmartGas

**Monitoramento de gás em tempo real com microcontrolador e envio de dados via HTTPS.**

O **SmartGas** é um projeto focado na leitura e transmissão de dados de sensores de gás. Desenvolvido em C++ para microcontroladores da família ESP8266, o sistema realiza a leitura dos níveis de gás, aloca os componentes de forma segura em uma case impressa em 3D e transmite as informações em tempo real para um servidor web seguro.

## 🚀 Funcionalidades

* **Conexão Wi-Fi:** Conecta-se automaticamente à rede local para habilitar o acesso à internet.
* **Comunicação Segura (HTTPS):** Utiliza a biblioteca `BearSSL` para garantir o envio criptografado dos dados para a nuvem, ignorando a validação de certificados locais para simplificar o protótipo.
* **Envio via GET Request:** Estrutura requisições HTTP GET contendo os valores de leitura do sensor como parâmetros na URL.
* **Intervalo Customizável:** Temporizador ajustável (atualmente configurado para envios a cada 15 segundos) para gerenciar o tráfego de rede e o consumo de energia.
* **Case 3D:** Estrutura física projetada e impressa em 3D para acomodar o microcontrolador e os sensores de forma protegida.

## 🛠️ Tecnologias Utilizadas

* **Linguagem:** C++
* **Hardware:** NodeMCU / Microcontrolador ESP8266
* **Bibliotecas:** * `ESP8266WiFi.h` (Gerenciamento de rede)
    * `ESP8266HTTPClient.h` (Requisições Web)
    * `WiFiClientSecureBearSSL.h` (Comunicação Criptografada)

## 💻 Estrutura do Código

O módulo de comunicação apresentado neste repositório é responsável por gerar/coletar o valor do gás (neste exemplo, simulado pela função `random()`) e concatenar esse valor à URL do servidor web (`enviar_dados.php?valor=X`). 

Se a conexão Wi-Fi estiver ativa, o ESP8266 inicia uma sessão HTTPS e transmite o pacote, aguardando e imprimindo o código de resposta HTTP (como HTTP 200 OK) no Monitor Serial.

## ⚙️ Como usar

1. Abra o arquivo na **Arduino IDE**.
2. Instale as placas da família ESP8266 no Gerenciador de Placas.
3. Altere as seguintes credenciais no código para as da sua rede:
   ```cpp
   const char* ssid = "NOME_DA_SUA_REDE";
   const char* password = "SENHA_DA_SUA_REDE";
