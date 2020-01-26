package misc;
import java.util.regex.Pattern;  

public class Regular_expression {  
	public static boolean isNumeric(String str) {  

		Pattern pattern = Pattern.compile("^[0-9]\\d{0,1}+$");  
		return pattern.matcher(str).matches();  
	}  
}  