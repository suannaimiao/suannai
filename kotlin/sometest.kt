package com.example.testactivity

import kotlin.math.max

fun largerNumber(num1: Int, num2: Int) = max(num1,num2)

fun getScore(name:String) = when (name) {
    "Tom" -> 86
    "Jim" -> 77
    "Jack" -> 95
    "Lily" -> 100
    else -> 0
}

fun checkNumber (num: Number){
    when (num){
        is Int -> println("Number is Int")
        is Double -> println("Number is Double")
        else -> println("Number not support")
    }
}



fun main() {
    val a = 37
    val b = 40
    val num =10
    val value = largerNumber(a, b)
    checkNumber(num)
    println("lager number is" +"  " +value)
}

