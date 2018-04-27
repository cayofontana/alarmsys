import java.io.FileInputStream;
import java.io.IOException;
import java.io.UnsupportedEncodingException;
import java.util.Arrays;
import java.util.Scanner;
import java.util.List;
import java.util.ArrayList;

import org.apache.http.HttpEntity;
import org.apache.http.HttpResponse;
import org.apache.http.client.HttpClient;
import org.apache.http.client.methods.HttpPost;
import org.apache.http.entity.StringEntity;
import org.apache.http.impl.client.HttpClientBuilder;
import org.apache.http.util.EntityUtils;

import com.google.api.client.googleapis.auth.oauth2.GoogleCredential;

class ServicoMovel {

	private static List<String> tokens;

	static
	{
		tokens = new ArrayList<String>();
		tokens.add("fQ3a7Rd0LZM:APA91bGJM21rM4iBHZI2xWRFfXuZWrERqoa2WnUBcfvN3jVsBjEvpdl5omtKiqrgRYOxdNlNKQa4ce3EGR54-3-uJO5vFN7TGn1X2tfY_p2Rkhb-JSAE3fTscPJHFsLohKtRVufsgK39");
		tokens.add("feY4iif98X4:APA91bGsRh3cLWRCsPk1Dlyt3wGZ069sd8eqb2cvqGbSnQ9Ew6b8hNuQoUW7kGRHCpCK58_j4sMdx78_e6UiIY01hwxtuiJcPgJtW8RrxJssbQzAkI6mcPSSUkOWwA2yEo6kVkcR40NE");
		tokens.add("fYwp2LOMfY0:APA91bESYYn2luC1HbKnhGw-96fMRVVibOp4xDHHvZvHj9NhWVE9j3uw2YuIRCoR7ADalstCJ5TQgI8uCOqwFNMjX4wvTkLkXUOI701GAKVCBdbR8QLtiiI7aJNQxyg9NCddAzLEjLA3");
		tokens.add("cVtCXX29Djw:APA91bEzwfUJ-oWKXy96Qb26OyBHICyfPwY7czNicWqLX6DBYyAEqThcy1shNFV1RY4doxhRkoNtiPMKt_B_u4KzlMLRd7tiqEX1aIQ9iy0UDKB81Z33BEhMZrs6uLefqrS0jtK8g52D");
	}

	//Endereço usado na solicitação de permissão do API do Google
	private static String SCOPE = "https://www.googleapis.com/auth/firebase.messaging";
	
	//Endereço para onde sera enviado o POST
	private static String url = "https://fcm.googleapis.com/v1/projects/fir-teste-c21fa/messages:send";

	public static void enviar(String mensagem)
	{
		for (String token : tokens)
			enviarMensagem(token, mensagem);
	}
	
	//Envia o POST
	private static void enviarMensagem(String token, String mensagem)
	{
		StringEntity postEntity;
		HttpClient client = HttpClientBuilder.create().build();
		
		try
		{
			HttpPost request = new HttpPost(url);
			request.addHeader("content-type", "application/json");
			request.addHeader("Authorization", "Bearer " + getAccessToken());
			postEntity = buildPostEntity(token, mensagem);
			request.setEntity(postEntity);
			
			HttpResponse response = client.execute(request); 
			HttpEntity responseEntity = response.getEntity();
			String responseString = EntityUtils.toString(responseEntity);
			System.out.println("\nResposta:\n" + responseString);
		}
		catch (Exception e)
		{
			System.out.println(e.getMessage());
		}
	}
	
	//Constrói uma StringEntity imitando uma estrutura JSON
	//(Porque eu não sei usar JSON)
	private static StringEntity buildPostEntity(String token, String body) throws UnsupportedEncodingException
	{
		String entity =
				"{\r\n" + 
				"  \"message\":{\r\n" + 
				"    \"token\" : \"" + token + "\",\r\n" + 
				"    \"notification\" : {\r\n" + 
				"      \"body\" : \"" + body + "\",\r\n" + 
				"      }\r\n" + 
				"   }\r\n" + 
				"}";
		
		return new StringEntity(entity);
	}
	
	//Pega um token de acesso do Google
	private static String getAccessToken() throws IOException {
	    GoogleCredential googleCredential = GoogleCredential
	        .fromStream(new FileInputStream("recursos/AccessToken.json"))
	        .createScoped(Arrays.asList(SCOPE));
	    googleCredential.refreshToken();
	    return googleCredential.getAccessToken();
	}

}
