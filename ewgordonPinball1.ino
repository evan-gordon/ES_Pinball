//Evan Gordon, Ryan
#define N_DISPLAYS 5   // up to 5 score displays 
#define N_DIGITS   6   // each with 6 BCD digits 
#define INCR    8353   // score incremen

volatile int DISP_ENABLED[N_DISPLAYS] = {26, 27, 28, 29, 38};
volatile int DISP[N_DISPLAYS][N_DIGITS] = {-1};

void setup() {
  Serial.begin(9600);
  DDRA = B11111111;
  attachInterrupt(2, dispIsr, RISING);
}

void loop() { // blank (not zero) all the displays by setting the score to -1 
  for (int i=0 ; i<N_DISPLAYS ; i++)
     for (int dig=0 ; dig<N_DIGITS ; dig++)
        DISP[i][dig] = dig ;
}

void setScore(int dispNumber, long int score)
{
  int scoreCpy = score;
  for(int i = 0; i < N_DIGITS; ++i)
    {DISP[dispNumber][i] = removeSmallestDigit(score);} 
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
  static int digit = 0;
  digitalWrite(A15, HIGH);
  digitalWrite((39 + digit), LOW);//set previous digit to low
  digit = (digit + 1) % 6;
  digitalWrite(A9, HIGH);
  for(int i = 0; i < N_DISPLAYS; ++i)
  {
    PORTA = DISP[i][digit];
    digitalWrite(DISP_ENABLED[i], HIGH);//what value is supposed to be inside disp_enabled
    digitalWrite(DISP_ENABLED[i], LOW);
  }
  digitalWrite(A9, LOW);
  digitalWrite((39 + digit), HIGH);
  digitalWrite(A15, LOW);
}

