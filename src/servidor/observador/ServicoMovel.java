package observador;

import java.io.FileInputStream;
import java.io.IOException;
import java.io.UnsupportedEncodingException;

import java.util.Arrays;
import java.util.List;
import java.util.ArrayList;
import java.util.Map;

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
	private static final String FCM_ENDPOINT = "https://fcm.googleapis.com/v1/projects/alarmsys-4c2f7/messages:send";

	private ServicoMovel()
	{
	}

	public static void enviarMensagem(List<Token> tokens, String mensagem, Map<String, String> valores)
	{
		StringEntity stringJSON;
		HttpClient clienteHttp = HttpClientBuilder.create().setRedirectStrategy(new LaxRedirectStrategy()).build();
		
		try
		{
			for (Token token : tokens)
			{
				HttpPost requisicaoHttp = new HttpPost(FCM_ENDPOINT);
				requisicaoHttp.addHeader("content-type", "application/json");
				requisicaoHttp.addHeader("Authorization", "Bearer " + getTokenAcesso());
				stringJSON = construirMensagemJSON(token.getId(), mensagem, valores);
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

	public static void receberMensagem(String token)
	{
	}

	private static StringEntity construirMensagemJSON(String token, String conteudo, Map<String, String> valores) throws UnsupportedEncodingException
	{
		// String stringJSON =	"{\r\n" + 
		// 	"\"message\":{\r\n" + 
		// 		"\"token\" : \"" + token + "\",\r\n" + 
		// 		"\"notification\" : { \r\n" + 
		// 			"\"title\" : \"SEAM Alerta!\",\r\n" + 
		// 			"\"body\" : \"" + conteudo + "\",\r\n" + 
		// 			"\"click_action\" : \"SEAM Alerta!\",\r\n" + 
		// 			"},\r\n" + 
		// 			"\"data\" : {\r\n";
		// 			int i = 0;
		// 			for (String chave : valores.keySet())
		// 			{
		// 				if (i < valores.size() - 1)
		// 					stringJSON += "\"" + chave + "\" : " + "\"" + valores.get(chave) + "\",\r\n";
		// 				else
		// 					stringJSON += "\"" + chave + "\" : " + "\"" + valores.get(chave) + "\"\r\n";
		// 				i++;
		// 			}
		// 		stringJSON += "} \r\n" + 
		// 		"} \r\n" +
		// 	"}";

		String stringJSON = "{\r\n" + 
				"\"message\":{\r\n" + 
					"\"token\" : \"" + token + "\",\r\n" + 
					"\"data\" : {\r\n";
						int i = 0;
						for (String chave : valores.keySet())
						{
							if (i < valores.size() - 1)
								stringJSON += "\"" + chave + "\" : " + "\"" + valores.get(chave) + "\",\r\n";
							else
								stringJSON += "\"" + chave + "\" : " + "\"" + valores.get(chave) + "\"\r\n";
							i++;
						}
					stringJSON += "} \r\n" + 
				"} \r\n" +
			"}";
		
		return (new StringEntity(stringJSON));
	}

	private static String getTokenAcesso() throws IOException
	{
		GoogleCredential credencialGoogle = GoogleCredential.fromStream(new FileInputStream("observador/recursos/alarmsys-4c2f7-firebase-adminsdk-hp4xq-375c23ca94.json")).createScoped(Arrays.asList(ESCOPO));
		credencialGoogle.refreshToken();

		return (credencialGoogle.getAccessToken());
	}
}