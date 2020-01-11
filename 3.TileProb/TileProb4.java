package hw10;

import java.util.List;
import java.util.ArrayList;

public class TileProb4 {

	/*
	 * Given a board of size 4×n 
	 * use 2x1 tiles to fill it
	 */

	
	public static void main(String[] args) {
		// TODO Auto-generated method stub
		List<Long> ans = waysToTile(new int[] {2,3,7});
		System.out.println(ans);
	}
	
	public static List<Long> waysToTile(int[] width){
		List<Long> ans = new ArrayList<>();
		for(int j = 0; j < width.length; j++) {
			int w = width[j];
			long[] f = new long[w+1];
			long[] g = new long[w+1];
			long[] h = new long[w+1];
			f[0] = f[1] = g[0] = h[0] = h[1] = 1;
			g[1] = 2;
			for(int i = 2; i <= w; i++){
				f[i] = f[i-1] + f[i-2] + 2*g[i-2] + h[i-2];
				g[i] = g[i-1] + f[i];
				h[i] = h[i-2] + f[i];
			}
			ans.add(f[w]);
		}
		return ans;
	}

}


/*
 * ***** another method: DP
 * https://math.stackexchange.com/questions/664113/count-the-ways-to-fill-a-4-times-n-board-with-dominoes
 */
