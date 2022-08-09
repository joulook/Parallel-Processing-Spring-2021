import java.lang.Math;
import java.io.IOException;
import java.io.FileWriter;
public class MakeFile{

	public static void main(String []args) throws IOException{
        FileWriter fw = new FileWriter("out.txt");
		for(int i = 0 ; i<1000000000 ; i++){
            int a = (int)(Math.random()*(1000-0+1)+0);
            int b = (int)(Math.random()*(1000-0+1)+0);
			fw.write(a+","+b+System.getProperty( "line.separator" ));
		}
		fw.close();
	}
}

