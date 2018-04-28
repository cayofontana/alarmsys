import java.io.FileInputStream;
import java.io.IOException;
import java.io.UnsupportedEncodingException;
import java.util.Arrays;
import java.util.List;
import java.util.ArrayList;

import org.apache.http.HttpEntity;
import org.apache.http.HttpResponse;
import org.apache.http.client.HttpClient;
import org.apache.http.client.methods.HttpPost;
import org.apache.http.entity.StringEntity;
import org.apache.http.impl.client.HttpClientBuilder;
import org.apache.http.impl.client.LaxRedirectStrategy;
import org.apache.http.util.EntityUtils;

import com.google.api.client.googleapis.auth.oauth2.GoogleCredential;

class ServicoMovel
{
	private static final String ESCOPO = "https://www.googleapis.com/auth/firebase.messaging";	
	private static final String ENDERECO_REQUISICAO = "https://fcm.googleapis.com/v1/projects/fir-teste-c21fa/messages:send";

	private static List<String> tokens;

	static
	{
		tokens = new ArrayList<String>();
		tokens.add("fQ3a7Rd0LZM:APA91bGJM21rM4iBHZI2xWRFfXuZWrERqoa2WnUBcfvN3jVsBjEvpdl5omtKiqrgRYOxdNlNKQa4ce3EGR54-3-uJO5vFN7TGn1X2tfY_p2Rkhb-JSAE3fTscPJHFsLohKtRVufsgK39");
		tokens.add("feY4iif98X4:APA91bGsRh3cLWRCsPk1Dlyt3wGZ069sd8eqb2cvqGbSnQ9Ew6b8hNuQoUW7kGRHCpCK58_j4sMdx78_e6UiIY01hwxtuiJcPgJtW8RrxJssbQzAkI6mcPSSUkOWwA2yEo6kVkcR40NE");
		tokens.add("fYwp2LOMfY0:APA91bESYYn2luC1HbKnhGw-96fMRVVibOp4xDHHvZvHj9NhWVE9j3uw2YuIRCoR7ADalstCJ5TQgI8uCOqwFNMjX4wvTkLkXUOI701GAKVCBdbR8QLtiiI7aJNQxyg9NCddAzLEjLA3");
		tokens.add("cVtCXX29Djw:APA91bEzwfUJ-oWKXy96Qb26OyBHICyfPwY7czNicWqLX6DBYyAEqThcy1shNFV1RY4doxhRkoNtiPMKt_B_u4KzlMLRd7tiqEX1aIQ9iy0UDKB81Z33BEhMZrs6uLefqrS0jtK8g52D");
	}

	public static void enviarMensagem(String mensagem)
	{
		StringEntity stringJSON;
		HttpClient clienteHttp = HttpClientBuilder.create().setRedirectStrategy(new LaxRedirectStrategy()).build();
		
		try
		{
			for (String token : tokens)
			{
				HttpPost requisicaoHttp = new HttpPost(ENDERECO_REQUISICAO);
				requisicaoHttp.addHeader("content-type", "application/json");
				requisicaoHttp.addHeader("Authorization", "Bearer " + getTokenAcesso());
				stringJSON = construirMensagemJSON(token, mensagem);
				requisicaoHttp.setEntity(stringJSON);

				HttpResponse respostaHttp = clienteHttp.execute(requisicaoHttp); 
				HttpEntity respostaJSON = respostaHttp.getEntity();
				String respostaStr = EntityUtils.toString(respostaJSON);

				System.out.println(respostaStr);
			}
		}
		catch (UnsupportedEncodingException excecao)
		{
			System.out.println(excecao);
		}
		catch (IOException excecao)
		{
			System.out.println(excecao);
		}		
	}

	private static StringEntity construirMensagemJSON(String token, String conteudo) throws UnsupportedEncodingException
	{
		String stringJSON =	"{\r\n" + 
				"  \"message\":{\r\n" + 
				"    \"token\" : \"" + token + "\",\r\n" + 
				"    \"notification\" : {\r\n" + 
				"      \"body\" : \"" + conteudo + "\",\r\n" + 
				"      }\r\n" + 
				"   }\r\n" + 
				"}";
		
		return (new StringEntity(stringJSON));
	}

	private static String getTokenAcesso() throws IOException
	{
		GoogleCredential credencialGoogle = GoogleCredential.fromStream(new FileInputStream("recursos/AccessToken.json")).createScoped(Arrays.asList(ESCOPO));
		credencialGoogle.refreshToken();

		return (credencialGoogle.getAccessToken());
	}
}