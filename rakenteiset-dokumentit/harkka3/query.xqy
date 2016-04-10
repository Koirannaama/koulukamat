<valuableVegetables>
{
for $v in doc("task3_valid_instance1.xml")/gameLevel/gameObjects/vegetables/vegetable
where $v/@points > 5
return $v
}
</valuableVegetables>