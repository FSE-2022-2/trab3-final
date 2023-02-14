# Trabalho Final - Fundamentos de Sistemas Embarcados

Este trabalho visa a criação de sensores e atuadores distribuídos baseados nos microcontroladores ESP32 conectados via Wifi através do protocolo MQTT.
Os microcontroladores ESP32 controlam a aquisição de dados dos botões e chaves além de acionar saídas de led e outros três dispositivos.

Mais especificações em: [Trabalho Final 2022.2.](https://gitlab.com/fse_fga/trabalhos-2022_2/trabalho-final-2022-2)

## Funcionalidades do sistema

Os componentes do sistema permitem:

- Leitura e envio dos valores de temperatura e umidade;
- Acionamento do LED RGB (Saída) à partir dos comandos RPC enviados pelo Dashboard de maneira dimerizável, com sua intensidade controlada à partir da técnica de PWM;
- Acionamento de botão Chave KY-004 que alterna a cor do LED quando acionado.
- Acionamento de um sensor de proximidade.
- Acionamento de um buzzer.
- Acionamento de um laser.

## Vídeo de demonstração 

[![Vídeo de demonstrção do projeto]()](https://)

## Instruções de uso

1. Clonar o repositório:

```
$ git clone https://github.com/FSE-2022-2/trab3-final.git
```

2. Para atualizar os dados de conexão wifi acesse o menu de configuração:
```
$ pio run -t menucofig
```

3. . O menu de configuração do projeto é: 
```
$ ** Project Configuration --->
```

4. Para rodar os servidores distribuídos instale extensão [Platform.IO](https://platformio.org/) no VsCode execute o comando: 

```
$ ...
```

5. O dashboard com a leitura dos dispositivos pode ser visualizado em [Ailamar-Guilherme-Matheus.](http://164.41.98.25:443/dashboards/43358ba0-aa58-11ed-8436-09bf763c9306)

## Dashboard

### Temperatura e humidade
...

### Sensores
...

