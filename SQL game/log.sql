"The CS50 Duck has been stolen!
The town of Fiftyville has called upon you to solve the mystery of the stolen duck.
Authorities believe that the thief stole the duck and then, shortly afterwards, took a flight out of town with the help of an accomplice.
Your goal is to identify:

Who the thief is.
What city the thief escaped to, and who the thief’s accomplice is who helped them escape.
All you know is that the theft took place on July 28, 2021 and that it took place on Humphrey Street."

-- Find informations about the crime
SELECT description
  FROM crime_scene_reports
 WHERE day = 28
   AND month = 07
   AND year = 2021
   AND street = "Humphrey Street";

"Theft of the CS50 duck took place at 10:15am at the Humphrey Street bakery.
Interviews were conducted today with three witnesses who were present at the time
each of their interview transcripts mentions the bakery
Littering took place at 16:36. No known witnesses."

-- Get informations from the interviews with the witnesses

SELECT name, transcript
  FROM interviews
 WHERE day = 28
   AND month = 07
   AND year = 2021;

"Ruth: Sometime within ten minutes of the theft, I saw the thief get into a car in the bakery parking lot and drive away.
       If you have security footage from the bakery parking lot, you might want to look
       for cars that left the parking lot in that time frame."

"Eugene: I don't know the thief's name, but it was someone I recognized.
         Earlier this morning, before I arrived at Emma's bakery, I was walking by the ATM on Leggett Street and
         saw the thief there withdrawing some money."

"Raymond: As the thief was leaving the bakery, they called someone who talked to them for less than a minute.
         In the call, I heard the thief say that they were planning to take the earliest flight out of Fiftyville tomorrow.
         The thief then asked the person on the other end of the phone to purchase the flight ticket."

-- Create a table of suspect from the parking lot records for a person who left within the 10:15 and 10:25 on the 28/07/21 as Ruth said in the interview

CREATE TABLE suspects AS
  SELECT people.id, people.name, people.phone_number, people.passport_number, people.license_plate
    FROM people
    JOIN bakery_security_logs
      ON bakery_security_logs.license_plate = people.license_plate
   WHERE bakery_security_logs.activity = "exit"
     AND bakery_security_logs.day = 28
     AND bakery_security_logs.month = 07
     AND bakery_security_logs.year = 2021
     AND bakery_security_logs.hour = 10
     AND bakery_security_logs.minute BETWEEN 15 AND 25;

-- Find informations on the suspects from the ATM machine: Luca, Bruce, Iman and Diana are the main suspects now

SELECT DISTINCT suspects.name, suspects.phone_number, suspects.passport_number, suspects.license_plate
  FROM suspects
  JOIN bank_accounts
    ON bank_accounts.person_id = suspects.id
  JOIN atm_transactions
    ON atm_transactions.account_number = bank_accounts.account_number
 WHERE atm_transactions.transaction_type = "withdraw"
   AND atm_transactions.day = 28
   AND atm_transactions.month = 07
   AND atm_transactions.year = 2021;

-- Update suspect table with the ATM machine results
DELETE
  FROM suspects
 WHERE NOT name = "Luca"
   AND NOT name = "Bruce"
   AND NOT name = "Iman"
   AND NOT name = "Diana";

-- Find informations on the caller and the receiver from the registry of calls

SELECT suspects.name, phone_calls.caller, phone_calls.receiver, phone_calls.duration
  FROM suspects
  JOIN phone_calls
    ON phone_calls.caller = suspects.phone_number
 WHERE phone_calls.duration BETWEEN 1 AND 60
   AND phone_calls.year = 2021
   AND phone_calls.month = 07
   AND phone_calls.day = 28
   AND phone_calls.caller = (SELECT suspects.phone_number FROM suspects WHERE suspects.name = "Luca")
    OR phone_calls.caller = (SELECT suspects.phone_number FROM suspects WHERE suspects.name = "Bruce")
    OR phone_calls.caller = (SELECT suspects.phone_number FROM suspects WHERE suspects.name = "Iman")
    OR phone_calls.caller = (SELECT suspects.phone_number FROM suspects WHERE suspects.name = "Diana");


-- Update suspect table: now Bruce and Diana are the only suspects left

DELETE
  FROM suspects
 WHERE NOT name = "Bruce"
   AND NOT name = "Diana";

 -- Find earliest flight on the 29th of July: at 8:20
 SELECT *
  FROM flights
  JOIN airports
    ON airports.id = flights.origin_airport_id
 WHERE flights.year = 2021
   AND flights.month = 07
   AND flights.day = 29;

-- Inspect the airport informations for the person who took the earliest flight on the 29th of July 2021.
SELECT suspects.name
  FROM suspects
  JOIN passengers
    ON passengers.passport_number = suspects.passport_number
  JOIN flights
    ON flights.id = passengers.flight_id
  JOIN airports
    ON airports.id = flights.origin_airport_id
 WHERE flights.year = 2021
   AND flights.month = 07
   AND flights.day = 29
   AND flights.hour = 8;

-- !! Bruce is the theft !! --

-- Find city where the theft escaped to
SELECT city
  FROM airports
 WHERE id = 4;

 -- !! New York !! --

-- Find the accomplice by looking at the name of the person who received the call
SELECT people.name, phone_calls.caller, phone_calls.receiver, phone_calls.duration
  FROM people
  JOIN phone_calls
    ON phone_calls.receiver = people.phone_number
 WHERE phone_calls.duration BETWEEN 1 AND 60
   AND phone_calls.year = 2021
   AND phone_calls.month = 07
   AND phone_calls.day = 28
   AND phone_calls.caller = (SELECT people.phone_number FROM people WHERE people.name = "Bruce");

-- !! Robin is the accomplice !! --






