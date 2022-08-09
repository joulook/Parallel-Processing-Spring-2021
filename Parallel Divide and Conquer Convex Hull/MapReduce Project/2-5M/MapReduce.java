import java.io.FileReader;
import java.io.BufferedReader;
import java.io.FileNotFoundException;
import java.io.IOException;
import java.io.FileWriter;
import java.io.BufferedWriter;
import java.util.Arrays;
public class MapReduce{

	public static void main(String []args) throws FileNotFoundException, IOException{
		BufferedReader csvReader = new BufferedReader(new FileReader(args[0]));
		int n = Integer.parseInt(args[1]);
		Point  p[] = new Point[n];
		String row="";
		for(int i = 0 ; i< n ; i++){
			row = csvReader.readLine();
			String[] data = row.split(",");
			Point o = new Point();
			o.x = Integer.parseInt(data[0]);
			o.y = Integer.parseInt(data[1]);
			p[i] = o;
		}
		csvReader.close();
		Point temp[] = new Point[n*2];
		int l = 0;
		int u = 0;
		for(int i=0 ; i<n ; i++){
		    while(l>=2 && determinan(temp[l-2],temp[l-1],p[i]) <= 0){
		        l--;
		    }
		    temp[l] = p[i];
		    l++;
		}
		
		u = l+1;
		for(int i=n-2 ; i>=0 ; i--){    
		    while(l>=u && determinan(temp[l-2],temp[l-1],p[i]) <= 0){
		        l--;
		    }
		    temp[l] = p[i];
		    l++;		    
		}
		if(l > 1){
		    temp = Arrays.copyOfRange(temp,0, l-1);
		}    
		BufferedWriter writer = new BufferedWriter(new FileWriter("final.txt", true));
		for(int i = 0 ; i<temp.length ; i++){
		    if(temp[i] != null){
		        writer.write(System.getProperty( "line.separator" )+temp[i].x+","+temp[i].y);
		    }
		}
		writer.close();
	}
	
	public static int determinan(Point a, Point b, Point c){
	    int d = (b.x-a.x)*(c.y-a.y) - (b.y-a.y)*(c.x-a.x);
	    return d;
	}
}
