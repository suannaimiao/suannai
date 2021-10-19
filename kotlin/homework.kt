package com.example.testactivity


fun main () {
    val x = arrayOf(74,71,72,68,76,73,67,70,65,74)
    val y = arrayOf(76,75,71,70,76,79,65,77,65,72)

   

    var i : Int = 0

    var sum = 0f
    var sum2 = 0f
    var sum3 = 0f
    var sum4 = 0f
  
  


    for(num in x){
        sum += num 
    }
    var average = sum / x.size

    for(num2 in y){
        sum2 += num2
    }
    var average2 = sum2 / y.size
 

    while(i<x.size){
      val num3 = x.get(i)*y.get(i) -average*average2
      sum3 += num3
    }
    while(i<y.size){
      val num4 = x.get(i)*x.get(i) - average*average
      sum4 += num4
    }
    println("线性回归方程："+ average2+"-"+sum3/sum4)
    
   

}