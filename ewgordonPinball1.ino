#define N_DISPLAYS 5   // up to 5 score displays 
#define N_DIGITS   6   // each with 6 BCD digits 
#define INCR    8353   // score incremen

int DISP_ENABLED[N_DISPLAYS] = {-1};
int DISP[N_DISPLAYS][N_DIGITS] = {-1};

void setup() {
  Serial.begin(9600);
  attachInterrupt(2, dispIsr, RISING);
  //might need to set some pins tooutput mode, see doc #6
  
}

void loop() { // blank (not zero) all the displays by setting the score to -1 
   
}

void setScore(int dispNumber, long int score)
{
  int scoreCpy = score;
  for(int i = 0; i < N_DIGITS; ++i)
  {
    DISP[dispNumber][i] = removeSmallestDigit(score);
  } 
  //make leading zeros -1?
}

int removeSmallestDigit(long int& score)//takes score splits off leading bit from original score
{
  int result = (int)(score % 10);
  score = score / 10;
  return result;
}

void dispIsr()
{
  for(int i = 0; i < N_DISPLAYS; ++i)
  {
    //stuff
    digitalWrite(DISP_ENABLED[i], HIGH);
    digitalWrite(DISP_ENABLED[i], LOW);
  }
}

