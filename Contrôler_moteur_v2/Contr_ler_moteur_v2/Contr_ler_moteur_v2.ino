#define pin_moteur 10
#define LDR_pin  = A0;

#define numReadings  = 100;
int readings [numReadings]; //Un tableau de int contenant 100 éléments
int readIndex  = 0;

float val;
long total  = 0;
int min_val = 89;
int max_val = 175;
int rpm;

void setup() {
  pinMode(pin_moteur,OUTPUT);
  //Défini la la pin analog en OUTPUT
  Serial.begin(9600);
  //défini la vitesse de communication du port sérielle USB
}

void loop() {
  val = smooth()/4;  
  //Fait une acquisition avec une moyenne glissante et convertie sur une échelle 8bits

  if(val < min_val){
    analogWrite(pin_moteur,min_val);
    //Envoyé au moteur la valeur minimum de sortie
    }
    
  else{
    int mappedVal = map(val,min_val,255,min_val,max_val);
    //Fait un ajustement linéaire pour ajuter la valeur de sortie selon la vittesse minimum et maximum du moteur
    analogWrite(pin_moteur,mappedVal);
    //Écrit la valeur sur la pin analogique du moteur
  }

long smooth() {

  long average; 
  //Créé un variable local pour la moyenne
  total = total - readings[readIndex];
  //Soustrait la valeur de l'indice du tableau
  readings[readIndex] = analogRead(LDR_pin);
  //Remplace la valeur de l'indice du tableau par une lecture analogique
  total = total + readings[readIndex];


  readIndex = readIndex + 1;
  if (readIndex >= numReadings) {
    readIndex = 0;
  }
  //Augmente l'indice et si il dépasse la limite le remettre à 0
  
  average = total / numReadings;
  //Calcule la moyenne et divisant le total par la grosseur du tableau
  return average;
  //Retourne la valeur moyenne
}
