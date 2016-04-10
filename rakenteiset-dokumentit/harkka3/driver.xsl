<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform"
				version="1.0">
				
	<xsl:output method="html" encoding="utf-8"/>
	
	<xsl:include href="gen.xsl"/>
		
	<xsl:template match="/gameLevel">
		<xsl:apply-templates/>
	</xsl:template>
	
	<xsl:template match="levelInfo">
		<xsl:message> 
		Processing level <xsl:value-of select="@name"/>
		</xsl:message>
		<h2><xsl:value-of select="@name"/></h2>
	</xsl:template>
	
	<xsl:template match="gameObjects">
		<xsl:apply-templates/>
	</xsl:template>
	
	<!-- Iterate over every child element in each game object category -->
	<xsl:template match="vegetables">
		<h3>Vegetables</h3>
		<xsl:for-each select="vegetable">
			<xsl:sort select="."/>
			<xsl:value-of select="."/> <br></br>
			<xsl:call-template name="description" />
		</xsl:for-each>
	</xsl:template>
	
	<xsl:template match="nonVegetables">
		<h3>Nonvegetables</h3>
		<xsl:for-each select="nonVegetable">
			<xsl:sort select="."/>
			<xsl:value-of select="."/><br></br>
			<xsl:call-template name="description"/>
		</xsl:for-each>
	</xsl:template>
	
	<xsl:template match="enemies">
		<h3>Enemies</h3>
		<xsl:for-each select="enemy">
			<xsl:sort select="."/>
			<xsl:value-of select="."/><br></br>
		</xsl:for-each>
	</xsl:template>
	
	<xsl:template match="powerUps">
		<h3>Power Ups</h3>
		<xsl:for-each select="powerUp">
			<xsl:sort select="."/>
			<xsl:value-of select="."/><br></br>
		</xsl:for-each>
	</xsl:template>
	
	<!-- Used when processing vegetable and nonVegetable objects to get the description attribute or adding "Missing a description" 
		 if the description couldn't be found-->
	<xsl:template name="description">
		<xsl:choose>
			<xsl:when test="@description">
				<span style="font-size: 12px"> 
					<xsl:value-of select="@description"/>
				</span><br></br>
			</xsl:when>
			<xsl:otherwise>
				<span style="font-size: 12px; color: red;"> 
					Missing a description
				</span><br></br>
			</xsl:otherwise>
		</xsl:choose>
	</xsl:template>
	
	<xsl:template match="*">
	</xsl:template>
	
</xsl:stylesheet>