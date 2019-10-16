int arrayLength = 256;
int * heapArray =(int *) malloc(arrayLength*sizeof(int));

void setup() {
 
  Serial.begin(115200);
  
}
 
void loop() {
  for(int i= 0; i<arrayLength; i++){
 
    heapArray[i] = analogRead(A0);
    //stackArray[i]=random(12);
    //Serial.print(stackArray[i]);
  }
  for(int i=0; i<arrayLength;i++){
    Serial.println(heapArray[i]);
  }
  delay(5000);
}
