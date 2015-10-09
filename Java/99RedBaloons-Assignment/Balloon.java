package pkg99redballoons;
import java.util.*;
//import javax.*;
import javax.swing.JOptionPane;
/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
/**
 */
public class Balloon {
    
   private int altitude=0;
   private String color="";
   

   
   
//   public void setColor()
//   {
//      color=JOptionPane.showInputDialog(null, "Please enter the color of the balloon");
//   }
   
    public void setColor(String stringer)
   {
      color=stringer;
   }
   
   public String getColor(){
       return ("".equals(color)? "The color hasn't been chosen": color);
       
   }
   
 
    
   public void increaseAltitude(int amount){
       
          altitude= altitude + amount;
          if(altitude<0){altitude=0;}
          
       
   } 
   
   public int getAltitude()
   {
       return altitude;
   }
   
   public boolean equals(Balloon balloon)
   {
       
       boolean isColorSame = this.getColor().equalsIgnoreCase(balloon.getColor());
       boolean isAltitudeSame= this.getAltitude()==balloon.getAltitude();
       return(isColorSame && isAltitudeSame);
           
   }
   
   
    
}
