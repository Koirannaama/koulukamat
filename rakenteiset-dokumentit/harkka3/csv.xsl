<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform"
				version="1.0">
				
	<xsl:output method="text" encoding="utf-8" indent="no"/>
	
	<xsl:include href="csv_generator.xsl"/>
	
	<xsl:template match="/gameLevel">
		<xsl:apply-templates/>
	</xsl:template>
	
	<!-- Add the name of the level before the acutal data. -->
	<xsl:template match="levelInfo">
		<xsl:value-of select="@name"/>
		<!-- Adds a newline character, doesn't seem to work in Notepad.-->
		<xsl:text>&#10;</xsl:text>
	</xsl:template>
	
	<xsl:template match="gameObjects">
		<xsl:apply-templates/>
	</xsl:template>
	
	<!-- Find every vegetable and fetch their points attributes-->
	<xsl:template match="vegetables">
		<xsl:for-each select="vegetable">
			<xsl:value-of select="@points"/>
			<xsl:text>,</xsl:text>
		</xsl:for-each>
		<!-- Adds a newline character, doesn't seem to work in Notepad.-->
		<xsl:text>&#10;</xsl:text>
	</xsl:template>
	
	<xsl:template match="*">
	</xsl:template>
				
</xsl:stylesheet>