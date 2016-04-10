<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform"
				version="1.0">
				
	<xsl:output method="html" encoding="utf-8"/>
	
	<xsl:template match="/collection">
		<html>
		<head>
		<style>
		h2 {
			color: blue;
		}
		
		body {
			font-family: sans-serif;
		}
		</style>
		</head>
			
		<body>
			<h1>Mr Green Genes: level info</h1>
			<xsl:for-each select="file">
				<xsl:apply-templates select="document(@href)"/>
			</xsl:for-each>
		</body>
		
		</html>	
	</xsl:template>
	
				
</xsl:stylesheet>