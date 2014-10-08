#include <SPI.h> //Inclui a biblioteca SPI.h
#include <Ethernet.h> //Inclui a biblioteca Ethernet.h


#define RELAY1  6                        
#define RELAY2  7                        
#define RELAY3  8                        
#define RELAY4  9

// Configurações para o Ethernet Shield
byte mac[] = { 0x90, 0xA2, 0xDA, 0x0D, 0x83, 0xEA }; // Entre com o valor do MAC

IPAddress ip(192,168,0,99); // Configure um IP válido 
byte gateway[] = { 192 , 168, 0, 255 }; //Entre com o IP do Computador onde a Câmera esta instalada
byte subnet[] = { 255, 255, 255, 0 }; //Entre com a Máskara de Subrede
EthernetServer server(80); //Inicializa a biblioteca EthernetServer com os valores de IP acima citados e configura a porta de acesso(80)

String A1_carga = "Rele 1"; //Função do primeiro botão
String A2_carga = "Rele 2"; //Função do segundo botão
String A3_carga = "Rele 3"; //Função do terceiro botão
String A4_carga = "Rele 4"; //Função do quarto botão

boolean A1_estado=false; //Variável para armazenar o estado do primeiro botão
boolean A2_estado=false; //Variável para armazenar o estado do segundo botão
boolean A3_estado=false; //Variável para armazenar o estado do terceiro botão
boolean A4_estado=false; //Variável para armazenar o estado do quarto botão

void setup(){    

  // Initialise the Arduino data pins for OUTPUT
  pinMode(RELAY1, OUTPUT);       
  pinMode(RELAY2, OUTPUT);
  pinMode(RELAY3, OUTPUT);
  pinMode(RELAY4, OUTPUT);
  Ethernet.begin(mac, ip);// Inicializa o Server com o IP e Mac atribuido acima

}

void loop(){
  acionamentos(); //Vai para a função que executa o acionamento dos botões
  EthernetClient client = server.available();// Verifica se tem alguém conectado
  if (client){
    boolean currentLineIsBlank = true; // A requisição HTTP termina com uma linha em branco Indica o fim da linha
    String valPag;
    
    while (client.connected()){
      if (client.available()){
        char c = client.read(); //Variável para armazenar os caracteres que forem recebidos
        valPag.concat(c); // Pega os valor após o IP do navegador ex: 192.168.1.2/0001  
        
         if(valPag.endsWith("0001")){
           A1_estado = !A1_estado;
           A2_estado = A2_estado;
           A3_estado = A3_estado;
           A4_estado = A4_estado;
         }
         
         else if(valPag.endsWith("0010")){
           A1_estado = A1_estado;
           A2_estado = !A2_estado; 
           A3_estado = A3_estado;
           A4_estado = A4_estado;        
         }
         
         else if(valPag.endsWith("0100")){
           A1_estado = A1_estado;
           A2_estado = A2_estado;
           A3_estado = !A3_estado;
           A4_estado = A4_estado;
         
         }
         else if(valPag.endsWith("1111")){
           A1_estado = A1_estado;
           A2_estado = A2_estado;
           A3_estado = A3_estado;
           A4_estado = !A4_estado;
         }
         //=========================================================================================================================
        if (c == '\n' && currentLineIsBlank)
        {
          //Inicia página HTML
          client.println("HTTP/1.1 200 OK");
          client.println("Content-Type: text/html");
          client.println();
          client.print("<HTML> ");
          
          client.println("<head>");
          client.println("<title>Consumo WWW</title>");
          client.println("<meta http-equiv='Content-Type' content='text/html; charset=ISO-8859-1'>");
          client.println("</head>");
          //=========================================================================================================================
          
          //Display da Temperatura
          /*
          if(COD>=B1000)
          {
            client.print("<BR>");

            client.print("<center>Temperatura do Sistema:  <font size=7>  <font color=\"#ff6600\">  ");
            client.print(temperature);
            client.print("*C </font></font></center>");
          }
          */
          //=========================================================================================================================

          client.println("<BODY>");
          
          client.print("<BR><BR>");

          //Primeiro BOTAO
          client.print("<center><button onclick=\"window.location.href='http://192.168.0.99/0001'\">\0</button> > Codigo: 0001 > ");
          if(A1_estado)
          {            
            client.print("<B><span style=\"color: #00ff00;\">");   
            client.print(A1_carga);
            client.print(" - OFF");     
            client.print("</span></B></center>");
          }         
          else
          {
            client.print("<B><span style=\"color: #ff0000;\">");
            client.print(A1_carga);
            client.print(" - ON");
            client.print("</span></B></center>");
          }
          //=========================================================================================================================


          //Segundo BOTAO
          client.print("<center><button onclick=\"window.location.href='http://192.168.0.99/0010'\">\0</button> > Codigo: 0010 > ");
          if(A2_estado)
          {
            client.print("<B><span style=\"color: #00ff00;\">");
            client.print(A2_carga);
            client.print(" - OFF");
            client.print("</span></B></center>");
          }
          else
          {
            client.print("<B><span style=\"color: #ff0000;\">");
            client.print(A2_carga);
            client.print(" - ON");
            client.print("</span></B></center>");
          }
          //=========================================================================================================================

          
          //Terceiro BOTAO
          client.print("<center><button onclick=\"window.location.href='http://192.168.0.99/0100'\">\0</button> > Codigo: 0100 > ");
          if(A3_estado)
          {
            client.print("<B><span style=\"color: #00ff00;\">");
            client.print(A3_carga);
            client.print(" - OFF");
            client.print("</span></B></center> ");
          }
          else
          {
            client.print("<B><span style=\"color: #ff0000;\">");
            client.print(A3_carga);
            client.print(" - ON");
            client.print("</span></B></center> ");
          } 
          //=========================================================================================================================
          
          //Quarto BOTAO
          client.print("<center><button onclick=\"window.location.href='http://192.168.0.99/1111'\">\0</button> > Codigo: 1111 > ");
          if(A4_estado){
            client.print("<B><span style=\"color: #00ff00;\">");
            client.print(A4_carga);
            client.print(" - OFF");
            client.print("</span></B></center> ");
          }
          else{
            client.print("<B><span style=\"color: #ff0000;\">");
            client.print(A4_carga);
            client.print(" - ON");
            client.print("</span></B></center> ");
          }
          //=========================================================================================================================      
          client.print(" <meta http-equiv=\"refresh\" content=\"5; url=http://192.168.0.99/\"> ");
          
          client.println("</BODY>");
          client.println("</HTML>");
          
          delay(1);
          client.stop();

          break;      
      
      }//if
      }
    }//while
  }//if
  
  
}//loop





void acionamentos(){ 
  if(A1_estado){
  	digitalWrite(RELAY1,HIGH);
  }
  else{
    digitalWrite(RELAY1,LOW);
  }
  
  //=========================================================================================================================
  
  //RELE 2 (ON/OFF) - 
  
  if(A2_estado){
    digitalWrite(RELAY2,HIGH);
  }
  else{
    digitalWrite(RELAY2,LOW);
  }
  
  //=========================================================================================================================

  //RELE 3 (ON/OFF)
  
  if(A3_estado){
    digitalWrite(RELAY3,HIGH);
  }
  else{ 
    digitalWrite(RELAY3,LOW);
  }
  
  //=========================================================================================================================
  //RELE 4 (ON/OFF)
  if(A4_estado){
    digitalWrite(RELAY4,HIGH);
  }
  else{ 
    digitalWrite(RELAY4,LOW);
  }
  //=========================================================================================================================

}
