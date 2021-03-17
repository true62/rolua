//Longest streak of chars in a string...should return 4(d's)

public static void Main(string[] args)
        {
            Console.WriteLine(Streak("aaabbCCC88ddddacC8"));
        }
public static int Streak(string s)
{
	int max = 0;
            int count = 0;

            for (int i = 1; i < s.Length; i++)
            {
                char currentLetter  = s[i];
                char previousLetter = s[i - 1];

                if (currentLetter == previousLetter) count++;
                if (count > max) max = count +1;
                if (currentLetter != previousLetter) count = 0;
            }

            return max;
}
---------------------------------------------------Option 1
public static int Streak(string s)
{
	int max = 0;

            for (int i = 0; i < s.Length; i++)
            {
                int count = 0;
                for (int j = i; j < s.Length; j++)
                {
                    if (s[i] == s[j]) count++;
                    if (count > max) max = count;
                    if (s[i] != s[j]) break;
                }
            }
            return max;
}
-----------------------------------------------------option 2

  public static string Streak(string s)
{
  Dictionary<char, int> dict = new Dictionary<char, int>();

  for (int i = 1; i < s.Length; i++)
  {
    //isolate char positions
    char currentLetter  = s[i];
    char previousLetter = s[i - 1];

    //Only if positions have matching char
    if (currentLetter == previousLetter)
    {
      //Increment existing(K,V) value by 1
      if (dict.ContainsKey(currentLetter))
        dict[currentLetter] = dict[currentLetter] + 1;

      //1st time that 2 positions match
      else if (!dict.ContainsKey(currentLetter))                   
      {
        dict.Add(currentLetter, 2);
      }
    }
  }
  //Sort High-Low based on (k,v) int value 
  var ordered = dict.OrderByDescending(dict => dict.Value)
    .ToDictionary(dict => dict.Key, dict => dict.Value);

  //Alternately --Take(1) highest count -or- var singleEntryDict = ordered.First();
  var result = ordered.Take(3).ToDictionary(d => d.Key, d => d.Value);

  var resultToString = string.Join(Environment.NewLine, result);

  return resultToString;
}
-----------------------------------------------------option 3
