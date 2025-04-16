-- Keep a log of any SQL queries you execute as you solve the mystery.
fiftyville/ $ sqlite3 fiftyville.db
sqlite> .tables
airports              crime_scene_reports   people
atm_transactions      flights               phone_calls
bakery_security_logs  interviews
bank_accounts         passengers
sqlite>
sqlite> SELECT *
   ...> FROM crime_scene_reports
   ...> WHERE year = 2024
   ...>   AND month = 7
   ...>   AND day = 28
   ...>   AND street = 'Humphrey Street';
+-----+------+-------+-----+-----------------+--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+
| id  | year | month | day |     street      |                                                                                                       description                                                                                                        |
+-----+------+-------+-----+-----------------+--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+
| 295 | 2024 | 7     | 28  | Humphrey Street | Theft of the CS50 duck took place at 10:15am at the Humphrey Street bakery. Interviews were conducted today with three witnesses who were present at the time – each of their interview transcripts mentions the bakery. |
| 297 | 2024 | 7     | 28  | Humphrey Street | Littering took place at 16:36. No known witnesses.                                                                                                                                                                       |
+-----+------+-------+-----+-----------------+--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+
sqlite>
sqlite> SELECT people.name from people
   ...> JOIN bank_accounts ON people.id = bank_accounts.person_id
   ...> JOIN atm_transactions ON atm_transactions.account_number = bank_accounts.account_number
   ...> WHERE atm_transactions.year = 2024 AND
   ...>  atm_transactions.month = 7 AND
   ...>  atm_transactions.day = 28 AND
   ...>  atm_transactions.atm_location = 'Leggett Street';
+---------+
|  name   |
+---------+
| Bruce   |
| Kaelyn  |
| Diana   |
| Brooke  |
| Kenny   |
| Iman    |
| Luca    |
| Taylor  |
| Benista |
+---------+
sqlite>
sqlite> SELECT DISTINCT people.name, people.license_plate
   ...> FROM people
   ...> JOIN bank_accounts ON people.id = bank_accounts.person_id
   ...> JOIN atm_transactions ON atm_transactions.account_number = bank_accounts.account_number
   ...> JOIN bakery_security_logs ON people.license_plate = bakery_security_logs.license_plate
   ...> WHERE atm_transactions.year = 2024
   ...>   AND atm_transactions.month = 7
   ...>   AND atm_transactions.day = 28
   ...>   AND atm_transactions.atm_location = 'Leggett Street'
   ...>   AND atm_transactions.transaction_type= 'withdrawing'
   ...>   AND bakery_security_logs.year = 2024
   ...>   AND bakery_security_logs.month = 7
   ...>   AND bakery_security_logs.day = 28;
   ...>   AND bakery_security_logs.hour = 10;
   ...>   AND bakery_security_logs.minute BETWEEN 15 AND 25
+--------+---------------+
|  name  | license_plate |
+--------+---------------+
| Luca   | 4328GD8       |
| Taylor | 1106N58       |
| Bruce  | 94KL13X       |
| Iman   | L93JTIZ       |
| Diana  | 322W7JE       |
+--------+---------------+
sqlite>
// Einer der Täter weil sie haben geld abgehoben und sind zwischen 10 15 und 10 30 vom parkplatz verschwunden
| Luca  | 4328GD8       |
| Bruce | 94KL13X       |
| Iman  | L93JTIZ       |
| Diana | 322W7JE
// Täter ist
 Bruce | 94KL13X       |
| Diana | 322W7JE

sqlite> SELECT DISTINCT people.name AS passenger_name,
   ...>                 origin_airports.city AS origin_city,
   ...>                 destination_airports.city AS destination_city
   ...> FROM people
   ...> JOIN bank_accounts ON people.id = bank_accounts.person_id
   ...> JOIN atm_transactions ON atm_transactions.account_number = bank_accounts.account_number
   ...> JOIN bakery_security_logs ON people.license_plate = bakery_security_logs.license_plate
   ...> JOIN phone_calls ON people.phone_number = phone_calls.caller
   ...> JOIN flights ON flights.origin_airport_id = origin_airports.id
   ...> JOIN airports AS origin_airports ON flights.origin_airport_id = origin_airports.id
   ...> JOIN airports AS destination_airports ON flights.destination_airport_id = destination_airports.id
   ...> JOIN passengers ON passengers.flight_id = flights.id
   ...> WHERE atm_transactions.year = 2024
   ...>   AND atm_transactions.month = 7
   ...>   AND atm_transactions.day = 28
   ...>   AND atm_transactions.atm_location = 'Leggett Street'
   ...>   AND atm_transactions.transaction_type = 'withdraw'
   ...>   AND bakery_security_logs.year = 2024
   ...>   AND bakery_security_logs.month = 7
   ...>   AND bakery_security_logs.day = 28
   ...>   AND bakery_security_logs.hour = 10
   ...>   AND bakery_security_logs.minute BETWEEN 15 AND 25
   ...>   AND phone_calls.year = 2024
   ...>   AND phone_calls.month = 7
   ...>   AND phone_calls.day = 28
   ...>   AND phone_calls.duration < 60
   ...>   AND flights.year = 2024
   ...>   AND flights.month = 7
   ...>   AND flights.day = 29
   ...> ORDER BY flights.hour, flights.minute
   ...> LIMIT 1;
+----------------+-------------+------------------+
| passenger_name | origin_city | destination_city |
+----------------+-------------+------------------+
| Diana          | Fiftyville  | New York City    |
+--------------
$ cd fiftyville/
fiftyville/ $ sqlite3 fiftyville.db
sqlite> SELECT DISTINCT people.name, people.license_plate
   ...> FROM people
   ...> JOIN bank_accounts ON people.id = bank_accounts.person_id
   ...> JOIN atm_transactions ON atm_transactions.account_number = bank_accounts.account_number
   ...> JOIN bakery_security_logs ON people.license_plate = bakery_security_logs.license_plate
   ...> WHERE atm_transactions.year = 2024
   ...>   AND atm_transactions.month = 7
   ...>   AND atm_transactions.day = 28
   ...>   AND atm_transactions.atm_location = 'Leggett Street'
   ...>   AND atm_transactions.transaction_type = 'withdraw'
   ...>   AND bakery_security_logs.year = 2024
   ...>   AND bakery_security_logs.month = 7
   ...>   AND bakery_security_logs.day = 28
   ...>   AND bakery_security_logs.hour = 10
   ...>   AND bakery_security_logs.minute BETWEEN 15 AND 25;
+-------+---------------+
| name  | license_plate |
+-------+---------------+
| Luca  | 4328GD8       |
| Bruce | 94KL13X       |
| Iman  | L93JTIZ       |
| Diana | 322W7JE       |
+-------+---------------+
sqlite> SELECT DISTINCT people.name, people.license_plate
   ...> FROM people
   ...> JOIN bank_accounts ON people.id = bank_accounts.person_id
   ...> JOIN atm_transactions ON atm_transactions.account_number = bank_accounts.account_number
   ...> JOIN bakery_security_logs ON people.license_plate = bakery_security_logs.license_plate
   ...> JOIN phone_calls ON people.phone_number = phone_calls.caller
   ...> WHERE atm_transactions.year = 2024
   ...>   AND atm_transactions.month = 7
   ...>   AND atm_transactions.day = 28
   ...>   AND atm_transactions.atm_location = 'Leggett Street'
   ...>   AND atm_transactions.transaction_type = 'withdraw'
   ...>   AND bakery_security_logs.year = 2024
   ...>   AND bakery_security_logs.month = 7
   ...>   AND bakery_security_logs.day = 28
   ...>   AND bakery_security_logs.hour = 10
   ...>   AND bakery_security_logs.minute BETWEEN 15 AND 25
   ...>   AND phone_calls.year = 2024
   ...>   AND phone_calls.month = 7
   ...>   AND phone_calls.day = 28
   ...>   AND phone_calls.duration < 60;
+-------+---------------+
| name  | license_plate |
+-------+---------------+
| Bruce | 94KL13X       |
| Diana | 322W7JE       |
+-------+---------------+
sqlite> SELECT DISTINCT people.name, people.license_plate
   ...> FROM people
   ...> JOIN bank_accounts ON people.id = bank_accounts.person_id
   ...> JOIN atm_transactions ON atm_transactions.account_number = bank_accounts.account_number
   ...> JOIN bakery_security_logs ON people.license_plate = bakery_security_logs.license_plate
   ...> JOIN phone_calls ON people.phone_number = phone_calls.caller
   ...> JOIN flights ON flights.origin_airport_id = 1  -- Angenommen, 1 ist der Airport-ID von Fiftyville
   ...> WHERE atm_transactions.year = 2024
   ...>   AND atm_transactions.month = 7
   ...>   AND atm_transactions.day = 28
   ...>   AND atm_transactions.atm_location = 'Leggett Street'
   ...>   AND atm_transactions.transaction_type = 'withdraw'
   ...>   AND bakery_security_logs.year = 2024
   ...>   AND bakery_security_logs.month = 7
   ...>   AND bakery_security_logs.day = 28
   ...>   AND bakery_security_logs.hour = 10
   ...>   AND bakery_security_logs.minute BETWEEN 15 AND 25
   ...>   AND phone_calls.year = 2024
   ...>   AND phone_calls.month = 7
   ...>   AND phone_calls.day = 28
   ...>   AND phone_calls.duration < 60
   ...>   AND flights.year = 2024
   ...>   AND flights.month = 7
   ...>   AND flights.day = 29
   ...> ORDER BY flights.hour, flights.minute
   ...> LIMIT 1;
sqlite> SELECT DISTINCT people.name, people.license_plate
   ...> FROM people
   ...> JOIN bank_accounts ON people.id = bank_accounts.person_id
   ...> JOIN atm_transactions ON atm_transactions.account_number = bank_accounts.account_number
   ...> JOIN bakery_security_logs ON people.license_plate = bakery_security_logs.license_plate
   ...> JOIN phone_calls ON people.phone_number = phone_calls.caller
   ...> JOIN flights ON flights.origin_airport_id = airports.id
   ...> JOIN airports ON airports.city = 'Fiftyville'
   ...> WHERE atm_transactions.year = 2024
   ...>   AND atm_transactions.month = 7
   ...>   AND atm_transactions.day = 28
   ...>   AND atm_transactions.atm_location = 'Leggett Street'
   ...>   AND atm_transactions.transaction_type = 'withdraw'
   ...>   AND bakery_security_logs.year = 2024
   ...>   AND bakery_security_logs.month = 7
   ...>   AND bakery_security_logs.day = 28
   ...>   AND bakery_security_logs.hour = 10
   ...>   AND bakery_security_logs.minute BETWEEN 15 AND 25
   ...>   AND phone_calls.year = 2024
   ...>   AND phone_calls.month = 7
   ...>   AND phone_calls.day = 28
   ...>   AND phone_calls.duration < 60
   ...>   AND flights.year = 2024
   ...>   AND flights.month = 7
   ...>   AND flights.day = 29
   ...> ORDER BY flights.hour, flights.minute
   ...> LIMIT 1;
+-------+---------------+
| name  | license_plate |
+-------+---------------+
| Diana | 322W7JE       |
+-------+---------------+
sqlite> SELECT DISTINCT people.name AS passenger_name, airports.city AS destination_city
   ...> FROM people
   ...> JOIN bank_accounts ON people.id = bank_accounts.person_id
   ...> JOIN atm_transactions ON atm_transactions.account_number = bank_accounts.account_number
   ...> JOIN bakery_security_logs ON people.license_plate = bakery_security_logs.license_plate
   ...> JOIN phone_calls ON people.phone_number = phone_calls.caller
   ...> JOIN flights ON flights.origin_airport_id = airports.id
   ...> JOIN airports ON airports.city = 'Fiftyville'
   ...> JOIN passengers ON passengers.flight_id = flights.id
   ...> JOIN airports AS destination_airport ON flights.destination_airport_id = destination_airport.id
   ...> WHERE atm_transactions.year = 2024
   ...>   AND atm_transactions.month = 7
   ...>   AND atm_transactions.day = 28
   ...>   AND atm_transactions.atm_location = 'Leggett Street'
   ...>   AND atm_transactions.transaction_type = 'withdraw'
   ...>   AND bakery_security_logs.year = 2024
   ...>   AND bakery_security_logs.month = 7
   ...>   AND bakery_security_logs.day = 28
   ...>   AND bakery_security_logs.hour = 10
   ...>   AND bakery_security_logs.minute BETWEEN 15 AND 25
   ...>   AND phone_calls.year = 2024
   ...>   AND phone_calls.month = 7
   ...>   AND phone_calls.day = 28
   ...>   AND phone_calls.duration < 60
   ...>   AND flights.year = 2024
   ...>   AND flights.month = 7
   ...>   AND flights.day = 29
   ...> ORDER BY flights.hour, flights.minute
   ...> LIMIT 1;
+----------------+------------------+
| passenger_name | destination_city |
+----------------+------------------+
| Diana          | Fiftyville       |
+----------------+------------------+
sqlite> SELECT DISTINCT people.name AS passenger_name,
   ...>                 origin_airports.city AS origin_city,
   ...>                 destination_airports.city AS destination_city
   ...> FROM people
   ...> JOIN bank_accounts ON people.id = bank_accounts.person_id
   ...> JOIN atm_transactions ON atm_transactions.account_number = bank_accounts.account_number
   ...> JOIN bakery_security_logs ON people.license_plate = bakery_security_logs.license_plate
   ...> JOIN phone_calls ON people.phone_number = phone_calls.caller
   ...> JOIN flights ON flights.origin_airport_id = origin_airports.id
   ...> JOIN airports AS origin_airports ON flights.origin_airport_id = origin_airports.id
   ...> JOIN airports AS destination_airports ON flights.destination_airport_id = destination_airports.id
   ...> JOIN passengers ON passengers.flight_id = flights.id
   ...> WHERE atm_transactions.year = 2024
   ...>   AND atm_transactions.month = 7
   ...>   AND atm_transactions.day = 28
   ...>   AND atm_transactions.atm_location = 'Leggett Street'
   ...>   AND atm_transactions.transaction_type = 'withdraw'
   ...>   AND bakery_security_logs.year = 2024
   ...>   AND bakery_security_logs.month = 7
   ...>   AND bakery_security_logs.day = 28
   ...>   AND bakery_security_logs.hour = 10
   ...>   AND bakery_security_logs.minute BETWEEN 15 AND 25
   ...>   AND phone_calls.year = 2024
   ...>   AND phone_calls.month = 7
   ...>   AND phone_calls.day = 28
   ...>   AND phone_calls.duration < 60
   ...>   AND flights.year = 2024
   ...>   AND flights.month = 7
   ...>   AND flights.day = 29
   ...> ORDER BY flights.hour, flights.minute
   ...> LIMIT 1;
+----------------+-------------+------------------+
| passenger_name | origin_city | destination_city |
+----------------+-------------+------------------+
| Diana          | Fiftyville  | New York City    |
+----------------+-------------+------------------+
