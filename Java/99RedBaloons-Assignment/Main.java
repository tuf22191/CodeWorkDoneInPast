/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package pkg99redballoons;

import java.util.*;
import java.awt.*;
import javax.swing.JOptionPane;
/**
 *
 * @author Jabrone
 */
public class Main {

    /**
     * @param args the command line arguments
     */
    public static void main(String[] args) {
       
             
       Balloon s1=new Balloon();
       Balloon s2=new Balloon();
       s1.setColor("Red");
       s1.increaseAltitude(50);
       s2.setColor("Blue"); 
       int altitudeS2=2*s1.getAltitude();
       s2.increaseAltitude(altitudeS2);
       System.out.println("s2= "+ s2.getAltitude());
       System.out.println("s2= "+ s2.getColor());
       System.out.println("s1= "+s1.getAltitude());
       System.out.println("s1= "+s1.getColor()+"\n\n");
       boolean areEqual;
       areEqual= s1.equals(s2);
       String notifyUser= areEqual==true?"equal":"not equal";
       JOptionPane.showMessageDialog(null, areEqual + ": So, the values are "+ notifyUser +".");
       s2.setColor("Red");
       double secondAltitudeS2= ((-90.0/s2.getAltitude())*100);
       s2.increaseAltitude((int) secondAltitudeS2);
       System.out.println("New data:\ns2= "+s2.getAltitude());
       System.out.println("s2= "+s2.getColor());
       s1.increaseAltitude(-s1.getAltitude()-100); //Sets altitude back to zero
                                              //then it subtracts an additional 100 to get -100 altitude
       s1.increaseAltitude(10);            
       System.out.println("s1= "+s1.getAltitude());
       System.out.println("s1= "+s1.getColor());
       areEqual= s1.equals(s2);
       notifyUser= areEqual==true?"equal":"not equal";
       JOptionPane.showMessageDialog(null, areEqual + ": So, the values are "+ notifyUser +".");
    
        
    }
    
}
