<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform"
				version="1.0">
				
	<xsl:output method="text" encoding="utf-8" indent="no"/>
	
	<xsl:strip-space elements="*"/>
	
	<xsl:template match="/collection">
			<xsl:for-each select="file">
				<xsl:apply-templates select="document(@href)"/>
			</xsl:for-each>
	</xsl:template>
	
				
</xsl:stylesheet>