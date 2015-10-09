
import javax.swing.*;
import java.util.*;

public class Bagels {
    private int randomNumber=0;
    private String randomNumberString ="";
    public int counter = 1;
    
    public void playGame(){
//         String number = JOptionPane.showInputDialog("Choose Your Difficulty: How long do you want the number to be?");
//            int lengthOf = Integer.parseInt(number);
//            generateNumber(lengthOf);
            generateSecretNumber();
            boolean continuePlaying= true;
            counter=1;
         
            do{
                  String input = JOptionPane.showInputDialog("Guess number");
                  boolean gotItRight=currentGuessIsWinner(input);
                  if(gotItRight){
                      JOptionPane.showMessageDialog(null, "Congradulations, you win!\nIndeed the number was " + randomNumber+
                              "\n You did it in " +counter+ " attempts!");
                      continuePlaying=false;
                  }
                  else{
                      evaluateGuess(input);
                      int continued = JOptionPane.showConfirmDialog(null, "Do you still want to play?");
                      continuePlaying= continued!=JOptionPane.NO_OPTION;
                  }
                  counter++;
            }while(continuePlaying);  
    }
    
    private void generateSecretNumber(){
            generateNumber(3);
            //System.out.print(randomNumber);
}

    private void generateNumber(int lengthOfNumber){
        
        lengthOfNumber--;
        String number;
        Random digit=new Random();
        int firstNumber=digit.nextInt(9)+1;
        number = Integer.toString(firstNumber);
        
        //0th element of string is a number from 1-9
        
        for(int i=1; i<lengthOfNumber+1;i++){
            int temp=digit.nextInt(10);
            String comparer=Integer.toString(temp);
            while(number.contains(comparer)){
              temp=digit.nextInt(10);
               comparer=Integer.toString(temp);}
            number = number + comparer;
        }
        randomNumberString=number;
        randomNumber=Integer.parseInt(number);
        
    }
    
    private boolean currentGuessIsWinner(String guesser)
    {   
        
        int guess = Integer.parseInt(guesser);
        return (guess==randomNumber || Integer.parseInt(randomNumberString)== guess);
//        if(guess==randomNumber || Integer.parseInt(randomNumberString)== guess)
//            return true;
//        else    
//            return false;
    }
    
    private void evaluateGuess(String guess)
    {
        int lengthOfGuess=guess.length();
        int bagelTeller=0;
       
        
        System.out.print("Guess # " + counter + "   Guess = "+ guess + "; ");
        for(int j=0;j< randomNumberString.length();j++){
            char picoValue= randomNumberString.charAt(j);
            for(int i=0;i<lengthOfGuess;i++){
                if(j==i && (randomNumberString.charAt(j)==guess.charAt(i)))   {
                    System.out.print("Fermi ");
                    bagelTeller=1;}
            }
        }
        
        for(int j=0;j< randomNumberString.length();j++){
          //  char picoValue= randomNumberString.charAt(j);
            for(int i=0;i<lengthOfGuess;i++){
                if(j!=i && (randomNumberString.charAt(j)==guess.charAt(i)))   {
                    System.out.print("Pico ");
                    bagelTeller=1;}
            }
        }
        
        if(bagelTeller==0){
            System.out.println("Bagels");
        }
        else
        {
            System.out.println("");
        }
        
        
//        String continued = JOptionPane.showInputDialog("Do you still want to play, don't quit!");
//        if(continued.contains("n")|| continued.contains("N"))
//        {
//            System.out.println(randomNumber + " was the number");
//            return false;
//        }
//        else
//        {
//            return true;
//        }
    
    
    }
}
