import Data.Char
import GHC.Exts.Heap (GenClosure (value))
import GHC.Integer (integerToInt)
import System.Environment (getArgs)
import Text.Read (Lexeme (Char))

main :: IO ()
main = do
  args <- getArgs
  contents <- readFile $ head args
  let strings = words contents

  putStrLn ("Result part1: " ++ show (calculateJoltage 2 strings))
  putStrLn ("Result part2: " ++ show (calculateJoltage 12 strings))

calculateJoltage :: Int -> [String] -> Int
calculateJoltage amountOfBatteries str = sum $ map (calculateLineJoltage amountOfBatteries) str

calculateLineJoltage :: Int -> String -> Int
calculateLineJoltage 0 str = 0
calculateLineJoltage 1 str = digitToInt $ findGreatestCharValue str
calculateLineJoltage amountOfBatteries str = value * (10 ^ (amountOfBatteries - 1)) + nextValue
  where
    nextValue = calculateLineJoltage (amountOfBatteries - 1) (substring str (valuePlace + 1) (length str))
    value = digitToInt $ str !! valuePlace
    valuePlace = findFirstIndexOf str (findGreatestCharValue $ substring str 0 (length str - (amountOfBatteries - 1)))

substring :: String -> Int -> Int -> String
substring str start end = take (end - start) (drop start str)

findFirstIndexOf :: String -> Char -> Int
findFirstIndexOf str value = aux str value 0
  where
    aux :: String -> Char -> Int -> Int
    aux [] _ _ = -1
    aux (x : xs) ch index = if x == ch then index else aux xs ch (index + 1)

findGreatestCharValue :: String -> Char
findGreatestCharValue [] = '0'
findGreatestCharValue [x] = x
findGreatestCharValue (x : xs) = max x (findGreatestCharValue xs)
