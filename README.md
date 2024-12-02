# trabalhoICM
repositório para arquivos do trabalho de introdução a comunicação móvel.

Fase 1: Preparação de ambiente de prototipagem

Hands-on 01: Github - o básico sobre repositórios
Objetivos
 Cadastramento no GitHub;
 Criar repositorios no GitHub;
 Submeter arquivos para repositórios do GitHub;
 Editar o README.md.
Hands-on 02: Básico do Jupyter Notebook
Objetivos
 Baixar, abrir, editar e criar Notebooks que executem blocos de código de Python (Python 3);
 Converter notebooks do Jupyter para PDF.
Hands-on 03: integrando ns3 com o VSCode
Objetivos
 Integrar o ns-3 com o VSCode.
Hands-on 04: integrando o ns-3 (cmake) com o VSCode
Objetivos
 Instalar o ns-3 (cmake) e dependências;
 Integrar o ns-3 (cmake) com o VSCode.

Frente 2: prototipagem com ns-3
Atividade 2.1: ler os capítulos 1, 2, 4, 5 e 6 do tutorial do ns-3
 Material Principal: an introduction into downloading, setting up, and using builtin models Tutorial ns-3
 Material Complementar: documentation on individual protocol and device models that build on the ns-3
core Model Library do ns-3
 Material Complementar: an in-depth coverage of the architecture and core of ns-3 Manual do ns-3
 Todo esse material pode ser encontrado em https://www.nsnam.org/releases/ns-3-43/documentation/

Atividade 2.2: entender o exemplo first.cc e acompanhar a leitura no Tutorial ns-3;
 Hands-on 01: Desafios relacionados ao exemplo first.cc
Objetivos
 Prática 01: envio de dois pacotes de tamanhos diferentes;
 Prática 02: mudança na taxa de transmissão.
Atividade 2.3: ler capítulo 7 do Tutorial ns-3.
Atividade 2.4: fazer e entender o exemplo second.cc e acompanhar a leitura no Tutorial ns-3.
 Hands-on 02: Desafios relacionados ao exemplo second.cc
Objetivos
 Prática 01: envio de dois pacotes de tamanhos diferentes sem criar novos objetos;
 Prática 02: aumentar número de nós via linha de comando;
 Prática 03: uso do tcpdump para insperção de arquivos pcap.
Atividade 2.5: fazer e entender o exemplo third.cc e acompanhar a leitura no Tutorial ns-3.
 Hands-on 03: Desafios relacionados ao exemplo third.cc
Objetivos
 Prática 01: envio de três pacotes de STAs diferentes;
 Prática 02: uso do NetAnim ou vis para verificar o movimento dos usuários.
Atividade 2.6: ler capítulo 8 do Tutorial ns-3.
 Hands-on 04: Desafios relacionados ao exemplo third.cc parte 2
Objetivos
 Prática 01: Mudar modelo de mobilidade, plotar as posições das STAs com o GNUPlot.
 Hands-on 05: Desafios relacionados ao exemplo fifth.cc
Objetivos
 Prática 01: uso do GNUPlot para visualizar a janela de congestionamento.
Atividade 2.7: ler capítulo 9 do Tutorial ns-3.
 Hands-on 06: Uso dos exemplos sixth.cc e seventh.cc
Objetivos
 Descrever os exemplos sixth.cc e seventh.cc;
 Gerar o gráfico do seventh.cc.
 Hands-on 07: Uso do exemplo rate-adaptation-distance.cc
Objetivos
 Descrever o exemplo rate-adaptation-distance.cc;
 Gerar o gráfico Throughput vs. Distância para os valores padrões do script.

Frente 3: Redes de Comunicações Móveis: Conhecendo o Wi-Fi - Roteiro de leituras:
 Atividade 3.1: Ler e resumir Seção 14.1: IEEE 802.11 Architecture and Services do Livro Wireless
Communications Networking (Stallings)
 Atividade 3.2: Ler e resumir Seção 14.2: IEEE 802.11 Medium Access Control do Livro Wireless
Communications Networking (Stallings)
 Atividade 3.3: Ler e resumir Seção 14.3: IEEE 802.11 Physical Layer do Livro Wireless Communications
Networking (Stallings)


Frente 4: Todos grupos devem criar dois cenários “WIFI 802.11” de simulações com as duas ementas que
preferirem (802.11n vs 802.11ax). Onde exista pelo menos um fluxo de dados em cada dispositivo (pelo menos 5
dispositivos) móvel que está presente na rede simulada. Para esse cenário tente extrair dados como:

Atraso (Delay), Variação do atraso (jitter), Perda de pacote(PLR) e taxa de dados(Throughput);