
import javax.swing.JOptionPane;

/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
/**
 *
 * @author Jabrone
 */
public class mainClass {

    /**
     * @param args the command line arguments
     */
    public static void main(String[] args) {
        // TODO code application logic here
        Bagels game = new Bagels();
        boolean playAgainOption=false;
        JOptionPane.showMessageDialog(null, "                            Welcome to the Pico, Fermi, Bagel Game!\n"
                + "\nTip: Remember that the number generated only has at most 1 of each digit.\n"
                + "This means that if the real number is 348, and you guess 444, the computer\n"
                + "will get a result of Fermi Pico Pico because the outer and inner 4's count\n"
                + "as having guessed the right value but not in the right place(Pico).\n"
                + "So, if you want, you can guess a number that has the same digit more than once\n"
                + "but proceed with caution.... :)");
        do{
           //game.counter=1;
           game.playGame();
           playAgainOption=wantsToPlayAgain();           
        }while(playAgainOption);
        JOptionPane.showMessageDialog(null,"Thank you and come again!");
        
    }
    
    private static boolean wantsToPlayAgain(){
        
        int response=JOptionPane.showConfirmDialog(null, "How about a new round?");
        return response!=JOptionPane.NO_OPTION;
        
//        String response= JOptionPane.showInputDialog("How about a new round?");
//        boolean letsSee;   
//            letsSee = response.contains("y") || response.contains("Y");
//        return letsSee;
    }
    
}
