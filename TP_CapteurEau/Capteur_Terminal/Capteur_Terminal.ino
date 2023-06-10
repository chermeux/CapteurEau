//********************** Déclaration des variables globales **********************//

//initialisation programme avec Led vérification si besoin
const int Aff = LED_BUILTIN;                                            // Aff LED de la carte
bool Etat = false;                                                      // Etat de l'affichage

// Constantes
const int SeuilAlert = 30;                                               // Seuil 30% à partir du moment qu'on est dans la réserve
const int VolumeMaxContenant = 264;                                      // en ml, issu de la question 5
const float TensionMaxOutConditionneur = 5.0;                            // en volt, issu de la question .......

// Déclaration Ports
const int PortConditionneur = A0;

//********************** Main **********************//
void setup() {
  pinMode (Aff ,OUTPUT);                                                  // Initialisation de Aff en sortie
  Serial.begin (9600);                                                    // Liaison série à 9600 bauds
  Serial.println(Aff);                                                    // Affichage de Aff
  Serial.println("Arduino Prêt");
}

void loop() {
  if(ReserveAlerte(ConversionTtoVol())== 1){                                
     Serial.println("Le volume est " + String(ConversionTtoVol()) + " mL. Nous sommes en réserve.");
  }
  else{
    Serial.println("Le volume est " + String(ConversionTtoVol()) + " mL.");
  }
  delay(1000);                                                            // Rafraichissement de 1 Hz

}

//********************** Déclaration des fonctions **********************//

// Fonction conversion de la tension en un volume
float ConversionTtoVol(){
  int lecturePortAnalog;
  float VolumeLu;
  float voltage;
  float Volume; 
  lecturePortAnalog = analogRead(PortConditionneur);                          // Lecture de la broche reliant arduino au conditionneur
  voltage = (float)lecturePortAnalog*(TensionMaxOutConditionneur/1023.0);     // analog read entre 0 et 1023, convert Tension en voltage
  VolumeLu = 5.1175*pow(voltage,4) - 37.139*pow(voltage,3) + 123.42*pow(voltage,2) - 152.08*voltage + 49.959;                                         // Conversion Voltage to mesure hauteur graduation
  Volume =  0.87*VolumeLu - 4.94;                                             // ******* TODO ******* ici indiquer formule/calculs pour convertir du voltage au volume en mL
  return(Volume);
 }

// Fonction vérification Volume > 30%
int ReserveAlerte(float volume){
  if(volume >= VolumeMaxContenant*SeuilAlert/100){
    return 0;                                                                 // Pas de souci on a plus de 30% du volume
  } 
  else{
    return 1;                                                                 // On est en réserve
  }
}

// Fonction test si problème téléversement
void LedArduino(){
  if(Etat){                                 // Si ( Etat = vrai ) alors
    digitalWrite(Aff ,LOW);                 // (Aff) <−− 0
  }                                         // Fin de s i
  else{                                     // Sinon
    digitalWrite(Aff ,HIGH);                // (Aff) <−− 1
  }                                         // Fin de sinon
  Etat = !Etat;
  delay (2000);                             // Attendre 2 secondes
 }
