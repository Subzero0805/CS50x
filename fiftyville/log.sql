-- Keep a log of any SQL queries you execute as you solve the mystery.

airports


.tables
.schema crime_scene_reports

SELECT * FROM crime_scene_reports
WHERE day = 28 AND month = 07 AND year = 2021;

.schema interviews

SELECT * FROM interviews
WHERE day = 28 AND month = 07 AND year = 2021;

SELECT * FROM bakery_security_logs
WHERE day = 28 AND month = 07 AND year = 2021 AND hour = 10 AND minute >= 15 AND minute <= 25;

SELECT * FROM people
WHERE license_plate in (
    SELECT license_plate FROM bakery_security_logs
    WHERE day = 28 AND month = 07 AND year = 2021 AND hour = 10 AND minute >= 15 AND minute <= 25);

SELECT * FROM atm_transactions
WHERE day = 28 AND month = 07 AND year = 2021 AND atm_location = "Leggett Street";

SELECT * FROM phone_calls
WHERE day = 28 AND month = 07 AND year = 2021 AND duration < 60;


SELECT * FROM phone_calls
WHERE day = 28 AND month = 07 AND year = 2021 AND duration < 60
AND caller in (
SELECT phone_number FROM people
WHERE license_plate in (
    SELECT license_plate FROM bakery_security_logs
    WHERE day = 28 AND month = 07 AND year = 2021 AND hour = 10 AND minute >= 15 AND minute <= 25));


SELECT * FROM people
WHERE phone_number in (
SELECT caller FROM phone_calls
WHERE day = 28 AND month = 07 AND year = 2021 AND duration < 60
AND caller in (
SELECT phone_number FROM people
WHERE license_plate in (
    SELECT license_plate FROM bakery_security_logs
    WHERE day = 28 AND month = 07 AND year = 2021 AND hour = 10 AND minute >= 15 AND minute <= 25 AND activity = "exit")));

SELECT * FROM flights
WHERE day = 29 AND month = 07 AND year = 2021 AND origin_airport_id =
(SELECT id FROM airports WHERE city = "Fiftyville");

SELECT passport_number FROM passengers
WHERE flight_id = (
SELECT id FROM flights
WHERE day = 29 AND month = 07 AND year = 2021 AND hour = 8 AND minute = 20 AND origin_airport_id =
(SELECT id FROM airports WHERE city = "Fiftyville"))
AND passport_number in (
SELECT passport_number FROM people
WHERE phone_number in (
SELECT caller FROM phone_calls
WHERE day = 28 AND month = 07 AND year = 2021 AND duration < 60
AND caller in (
SELECT phone_number FROM people
WHERE license_plate in (
    SELECT license_plate FROM bakery_security_logs
    WHERE day = 28 AND month = 07 AND year = 2021 AND hour = 10 AND minute >= 15 AND minute <= 25 AND activity = "exit")))
);

SELECT * FROM people
WHERE passport_number in (
SELECT passport_number FROM passengers
WHERE flight_id = (
SELECT id FROM flights
WHERE day = 29 AND month = 07 AND year = 2021 AND hour = 8 AND minute = 20 AND origin_airport_id =
(SELECT id FROM airports WHERE city = "Fiftyville"))
AND passport_number in (
SELECT passport_number FROM people
WHERE phone_number in (
SELECT caller FROM phone_calls
WHERE day = 28 AND month = 07 AND year = 2021 AND duration < 60
AND caller in (
SELECT phone_number FROM people
WHERE license_plate in (
    SELECT license_plate FROM bakery_security_logs
    WHERE day = 28 AND month = 07 AND year = 2021 AND hour = 10 AND minute >= 15 AND minute <= 25 AND activity = "exit")))
))
AND id in (
SELECT id FROM people
WHERE id in (
SELECT person_id FROM bank_accounts
WHERE account_number in (
SELECT account_number FROM atm_transactions
WHERE day = 28 AND month = 07 AND year = 2021 AND atm_location = "Leggett Street")));

SELECT * FROM phone_calls
WHERE caller =
(SELECT phone_number FROM people
WHERE name = "Bruce") AND day = 28 AND month = 07 AND year = 2021 AND duration < 60;

SELECT * FROM people
WHERE phone_number =
(SELECT receiver FROM phone_calls
WHERE caller =
(SELECT phone_number FROM people
WHERE name = "Bruce") AND day = 28 AND month = 07 AND year = 2021 AND duration < 60);