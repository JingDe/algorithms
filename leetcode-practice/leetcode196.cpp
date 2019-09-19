
SELECT p1.*
FROM Person p1, Person p2
WHERE p1.Email=p2.Email


SELECT p1.*
FROM Person p1, Person p2
WHERE p1.Email=P2.Email  AND p1.Id>P2.Id


DELETE p1 
FROM Person p1, Person P2
WHERE p1.Email=p2.Email AND p1.Id>p2.id
